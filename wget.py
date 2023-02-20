import wget
import os

str1 = "https://www.ncei.noaa.gov/data/sea-surface-temperature-optimum-interpolation/v2.1/access/avhrr/"
str2 = "oisst-avhrr-v02r01."
str3 = ".nc"
for year in range(1981, 1982):
    for month in range(9, 11):
        for day in range(15, 20):
            url = str1 + "{}".format(year) + "{:02d}".format(month) + "/" + str2 + "{}".format(
                year)+"{:02d}".format(month) + "{:02d}".format(day) + str3
            path1 = '../avhrr-only'
            file_path = os.path.join(
                path1, "{}".format(year), "{:02d}".format(month))
            if not os.path.exists(file_path):
                os.makedirs(file_path)

            try:
                wget.download(url, out=file_path)
            except:
                print("File:" + str2 + "{0}{1:02d}{2:02d}".format(year,
                      month, day) + str3 + " does not exist")
