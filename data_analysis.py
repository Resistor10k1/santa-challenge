import numpy as np
import math
import matplotlib.pyplot as plt
import pandas as pd
from haversine import haversine


with open('data/gifts.csv', mode='r') as csv_file:
    gift_df = pd.read_csv(csv_file, sep=',', dtype=float)
    print(gift_df.head())

gift_df = gift_df.sample(n=300)

print(f"Maximum weight: {max(gift_df['Weight'].to_numpy())}")
print(f"Minimum weight: {min(gift_df['Weight'].to_numpy())}")
print(f"Mean weight: {np.mean(gift_df['Weight'].to_numpy())}")
print(f"Median weight: {np.median(gift_df['Weight'].to_numpy())}")

north_pole = (90.0, 0.0)
dist_list = []

for latitude, longitude in zip(gift_df['Latitude'].to_numpy(), gift_df['Longitude'].to_numpy()):
    dist_list.append(haversine(north_pole, (latitude, longitude)))

gift_df['Distance'] = dist_list

cpp_dist = []
with open('data/output_dist.txt', mode='r') as f:
    cpp_dist = f.readlines()

cpp_calc_ok = True
for d_cpp, d_py in zip(cpp_dist, dist_list):
    if not math.isclose(float(d_cpp), float(d_py), abs_tol=0.000999):
        cpp_calc_ok = False

print(f"Are C++ calculations ok?: {cpp_calc_ok}")
print(f"Maximum distance: {max(dist_list)}")
print(f"Minimum distance: {min(dist_list)}")
print(f"Mean distance: {np.mean(dist_list)}")
print(f"Median distance: {np.median(dist_list)}")


plt.figure('Gift weights')
plt.plot(gift_df['GiftId'].to_numpy(), gift_df['Weight'].to_numpy(), '.')
# plt.vlines(gift_df["GiftId"].to_numpy(), 0.0, gift_df["Weight"].to_numpy(), linestyles='solid')
plt.xlabel("Gift ID")
plt.ylabel("Weight")
plt.grid(True)

plt.figure('Gift distances to north pole')
plt.plot(gift_df['GiftId'].to_numpy(), gift_df['Distance'].to_numpy(), '.', color='r')
# plt.vlines(gift_df["GiftId"].to_numpy(), 0.0, gift_df["Weight"].to_numpy(), linestyles='solid')
plt.xlabel("Gift ID")
plt.ylabel("Distance km")
plt.grid(True)

# plt.figure(1)
# counts, bins = np.histogram(gift_df['Weight'].to_numpy(), bins=15)
# plt.hist(counts, bins)
# plt.xlabel("Weight")
# plt.ylabel("Number of gifts")
# plt.grid(True)

plt.show()

