import csv
import struct

bin_ismi = 'LOG2461' #Bunu degistir yeter
bin_uzantisi = '.BIN' # Ya da bu gerekirse

def bin_den_csv_ye(bin_dosya_yolu, csv_dosya_yolu, format, basliklar):
    kayit_boyutu = struct.calcsize(format)

    with open(bin_dosya_yolu, 'rb') as bin_dosyasi, open(csv_dosya_yolu, 'w', newline='') as csv_dosyasi:
        yazici = csv.writer(csv_dosyasi)

        # once bizim belirledigimiz basliklari yazcaz
        yazici.writerow(basliklar)
        bin_dosyasi.seek(512)
        while True:
            bin_adimi = bin_dosyasi.read(kayit_boyutu)
            # demek ki okuyamadiginda False veriyor
            if not bin_adimi:
                break

            if len(bin_adimi) < kayit_boyutu:
                print(f'Son {len(bin_adimi)} bit okunmadi. Formatla uyusmazlik var.')
                break

            acik_veri = struct.unpack(format, bin_adimi)

            yazici.writerow(acik_veri)
    print(f'LOG {csv_dosya_yolu} ya kaydedildi.')


basliklar_aktuator = []
formatim = '<2xI' + '14f' *4 + '15fHHff6BfH'

ACT_FIELDS = [
    "current_measured",
    "current_demand",
    "valveAngle",
    "valveAngleKalman",
    "valveVelocity",
    "duty",
    "speedDemand",
    "pos_ref",
    "pos_ref_rate_limited",
    "speed_ref_rate_limited",
    "nozzle_pressure",
    "pressure_demand",
    "thrust_demand",
    "thrust_estimated",
]

sensor_bro = [
    "manifold_pressure",
    "thrust_measured",
    "quaternion_i",
    "quaternion_j",
    "quaternion_k",
    "quaternion_r",
    "linAccel_x",
    "linAccel_y",
    "linAccel_z",
    'angularVelocity_x',
    'angularVelocity_y',
    'angularVelocity_z',
    'angularVelocityDemand_x',
    'angularVelocityDemand_y',
    'angularVelocityDemand_z',
    "lidarDistance",
    "lidarStrength",
    "kf_altitude",
    "kf_velocity",
    'actuator_mode',
    'mission_modes',
    'system_modes',
    'last_error',
    'go_no_go_status',
    'go_no_go_enabled',
    'battery_voltage',
    "crc",
]


for i in range(4): # Actuator sayisi
    for baslik in ACT_FIELDS:
        basliklar_aktuator += [f"{baslik}_{i}"]

basliklar = ["timestamp"] + basliklar_aktuator + sensor_bro

bin_dosyaismi = bin_ismi + bin_uzantisi

bin_dosya_yolu = f'./{bin_dosyaismi}'
csv_dosya_yolu =  rf"C:\Users\egeel\Desktop\New folder\{bin_ismi}.csv"

bin_den_csv_ye(bin_dosya_yolu, csv_dosya_yolu, formatim, basliklar)