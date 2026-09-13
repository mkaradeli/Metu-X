t = out.x.Time;
x = out.x.Data(:);   v = out.v.Data(:);   a = out.a.Data(:);
assert(isequal(numel(x),numel(v),numel(a)),'signals logged on different clocks');

dx = diff(x);
fprintf('n=%d  x in [%.3f %.3f]  incr=%d  decr=%d\n', ...
        numel(x), min(x), max(x), all(dx>=0), all(dx<=0));



h  = 0.05;
tol = 1e-9;                                   % guard against 2.9999997-style endpoints
n0 = ceil (min(x)/h - tol);
n1 = floor(max(x)/h + tol);
xq = (n0:n1).' * h;                           % 0:0.1:3 → 31 points

[xu,iu] = unique(x);                          % interp1 needs *distinct* breakpoints
fprintf('dropped %d duplicate x samples\n', numel(x)-numel(xu));

vq = interp1(xu, v(iu), xq, 'linear');
aq = interp1(xu, a(iu), xq, 'linear');

for s = ["v" "a"]
    f  = eval(s); fq = eval(s+"q");
    e  = interp1(xq, fq, xu, 'linear') - f(iu);
    fprintf('%s: max %.4g (%.3f%% of range %.4g), rms %.4g\n', ...
            s, max(abs(e)), 100*max(abs(e))/range(f), range(f), rms(e));
end

fprintf('xu: %.17g  %.17g\nxq: %.17g  %.17g\n', xu(1), xu(end), xq(1), xq(end));
fprintf('NaN  vq %d  aq %d  |  source  v %d  a %d\n', ...
        nnz(isnan(vq)), nnz(isnan(aq)), nnz(isnan(v)), nnz(isnan(a)));

close all
plot(xq, vq)
hold on
plot(out.x.Data, out.v.Data)

save("drop_lookup_table.mat","xq","vq","aq");