# from pyforest import *
import numpy as np
import statsmodels.formula.api as smf
import pandas as pd
from sklearn.preprocessing import StandardScaler
import sklearn.linear_model as lrs
import matplotlib.pyplot as plt
import seaborn as sns
import warnings
from sklearn.model_selection import KFold
import math
from scipy import stats
from sklearn.neighbors import KNeighborsRegressor
from sklearn.model_selection import train_test_split
from sklearn.ensemble import AdaBoostRegressor
from sklearn.tree import DecisionTreeRegressor
warnings.filterwarnings("ignore")  # 过滤掉警告的意思
lamda = 0.2
df = pd.read_csv('time.csv')
X = df['index']+10
y = df['whole']
est = smf.ols(formula='whole~index', data=df).fit()
y_pred = est.predict(X)
df['whole_pred'] = y_pred
print(df)
print(est.summary())
print(est.params)


def funcation(x):
    return 1/(1.372452e-7*x-7.497738e-8)


def funcation1(x):
    return (8.899895e+06/x)+1.859866e+04


print(funcation(14))

df = pd.read_csv('day.csv')
df1 = pd.read_csv('week1.csv')
whole_week = df1[:]['F5']
# print(df.head())
whole_peo = df[:]['F5']
# print(whole_peo)


df2 = pd.read_csv('time.csv')
sub = []
colom = df2[:]['wholl']
for i in range(5, 12):
    sub.append(colom[i-1]-funcation(i))
# print(sub)
np_std = np.std(sub)
print(np_std)
print(funcation(14))

print('['+str(((funcation(14)-np_std*1.64)/31)*((lamda * (31*1071492/whole_peo.sum())) + (1-lamda)*(7*4786064/whole_week.sum()))) +
      ','+str(((funcation(14)+np_std*1.64)/31)*((lamda * (31*1071492/whole_peo.sum())) + (1-lamda)*(7*4786064/whole_week.sum())))+']')

df = pd.read_table('30k.txt')
# print(df.head())
colom1 = df[:]['the']
# print(colom1.size)
# print(colom1)
five_lettle = []
for i in range(0, 29999):
    if len(str(colom1[i])) == 5:
        five_lettle.append(colom1[i])

columns = ["letter"]
df3 = pd.DataFrame(columns=columns, data=five_lettle)
df3.to_csv('five_letters.csv')
df0 = pd.read_csv('data.csv')
# print(df0.head())
word = df0['Word']
print(word)
df4 = pd.read_csv('five_letters.csv')
index = []
words = []
notin = []
for i in range(0, 355):
    for j in range(0, 3634):
        if word[i] == df4['letters'][j]:
            index.append(df4['index'][j])
            words.append(df4['letters'][j])
            break
        elif j == 3633:
            index.append(-1)
            words.append(word[i])
columns = ['index']
df5 = pd.DataFrame(columns=columns, data=index)
df5['words'] = words
df5.to_csv("ranking.csv")

df9 = pd.read_csv('five_letters1.csv')
df10 = pd.read_csv('rating1.csv')
print(df10)
print(df9)

# print(df9['a'][0])

h = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
temp = 0
temp1 = 0
likely = []
for i in range(0, 355):
    temp1 = 0
    for k in range(0, 3740):
        temp = 0
        for p, j in enumerate(h):
            if df9[j][k] == 1 and df10[j][i] == 1:
                temp += 1
        if temp >= 4:
            temp1 += 1
    likely.append(temp1)
df11 = pd.DataFrame(columns=["likely"], data=likely)
df11.to_csv("likely.csv")


colom = [[]]
table = [[]]
masa = [-1]
temp = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
h = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
df6 = pd.read_csv('data.csv')
# print(df6)
colon = df6['Word']
# print(colon)
for i in colon:
    temp = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    masa.append(5)
    for index, word in enumerate(h):
        if word in i:
            temp[index] = 1
    colom.append(temp)

lat = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
       'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
per = pd.DataFrame(columns=lat, data=colom)
per.to_csv("rating1.csv")


df7 = pd.read_csv('1.csv')
coll = df7['cigen']
coll1 = []
for i in coll:
    if len(str(i)) > 1 and len(str(i)) < 4:
        coll1.append(i)
df8 = pd.DataFrame(data=coll1, columns=["wordstart"])
df8.to_csv('new.csv')


df11 = pd.read_csv('letter.csv')
df12 = pd.read_csv('data.csv')
word = ''
ans = []
lottary = 1
# print(df11)
# print(df12)
h1 = ['ha', 'hb', 'hc', 'hd', 'he']
lat = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
       'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

print(df11['ha'][12])
for i in range(0, 355):
    lottary = 1
    word = df12['Word'][i]
    for p, q in enumerate(h1):
        for j, k in enumerate(lat):
            if word[p] == k:
                lottary *= df11[q][j]
                break
    ans.append(lottary)

for i in range(0, 355):
    lottary = 1
    word = df12['Word'][i]
    for p in range(0, 5):
        for j, k in enumerate(lat):
            if word[p] == k:
                lottary *= df11['sum1'][j]
                break
    ans.append(lottary)

df13 = pd.DataFrame(data=ans, columns=["lottary"])
df13.to_csv('lottary.csv')

df14 = pd.read_csv('end.csv')
df15 = pd.read_csv('data.csv')
print(df14)
print(df15)
colonms = df14['wordstart']

temp = 0
ans1 = []
for i in range(0, 355):
    temp = 0
    for j in colonms:
        if j in df15['Word'][i]:
            temp += 1
    ans1.append(temp)
df16 = pd.DataFrame(data=ans1, columns=['struct'])
df16.to_csv('struct.csv')


df17 = pd.read_csv('data1.csv')
# print(df17.columns)
try1 = df17['1 try']
try2 = df17['2_tries']
try3 = df17['3_tries']
try4 = df17['4 tries']
try5 = df17['5 tries']
try6 = df17['6 tries']
try7 = df17['7 or more tries (X)']
repet = df17['repet']

#struct = df17['struct']


letter = df17['letter_lottary']
rank = df17['ranking']
word_likely = df17['word_likely']
place = df17['place_lottary']

letter_std = (letter-np.mean(letter))/np.std(letter)
rank_std = (rank-np.mean(rank))/np.std(rank)
# rank_std = np.log(rank_std)
word_likely_std = (word_likely-np.mean(word_likely))/np.std(word_likely)
place_std = (place-np.mean(place))/np.std(place)

letter_std = np.log(letter_std+20)

df18 = pd.DataFrame(data=try1, columns=['1 try'])
df18['2 try'] = try2
df18['3 try'] = try3
df18['4 try'] = try4
df18['5 try'] = try5
df18['6 try'] = try6
df18['7 try'] = try7
df18['rank'] = rank_std
df18['repet'] = repet
df18['word_likely'] = word_likely_std
#df18['struct'] = struct
df18['place_lottary'] = place_std
df18['letter_lottary'] = letter_std
df18.to_csv('data2.csv')
corr = df18.corr()
print(corr)
ax = plt.subplots(figsize=(20, 16))  # 调整画布大小
# 画热力图   annot=True 表示显示系数
ax = sns.heatmap(corr, square=True, annot=True, fmt=".3f", linewidths=.5,
                 cmap="YlGnBu", cbar_kws={"fraction": 0.046, "pad": 0.03})
# # 设置刻度字体大小
plt.xticks(fontsize=5)
plt.yticks(fontsize=5)
plt.show()
r, p = stats.pearsonr(rank_std, (try7-np.mean(try7))/np.std(try7))
print(p)

df17 = pd.read_csv('data1.csv')
X = df17.iloc[:, 7:12].values
y = df17['2_tries'].values
est = smf.ols(formula="2_tries~3_tries", data=df17).fit()
# y_pred = est.predict(X)
# df17['whole_pred'] = y_pred
# print(df18)
print(est.summary())
print(est.params)

ss = StandardScaler()
X_std = ss.fit_transform(X)


X = df17[['2_tries', '5 tries', '3_tries', '6 tries',
          '4 tries', '7 or more tries (X)']].values
y = df17['1 try'].values

lin = lrs.LinearRegression()
lin.fit(X, y)
print(lin.coef_)
print(lin.intercept_)
print(lin.score(X, y))

kf = KFold(n_splits=5, shuffle=False)
x_train, x_test, y_train, y_test = train_test_split(X_std, y, train_size=0.8)
# std_x = StandardScaler()
# std_y = StandardScaler()
# for x_train, x_test, y_train, y_test in kf.split(X_std, y, groups=10):
clf = KNeighborsRegressor(n_neighbors=8)
clf.fit(x_train, y_train)
print(clf.score(x_test, y_test))


X.reshape(-1, 1)
y.reshape(-1, 1)
lr = lrs.LinearRegression()
lr.fit(X, y)
print(lr.coef_)
print(lr.intercept_)
print(lr.score(X, y))

X = df17.iloc[:, 8:13].values
X1 = np.array([2, 0, 0.000227313, 0.0000055540155526, 61800])
y1 = df17['2_tries'].values
y2 = df17['5 tries'].values
# X1 = np.array([2896, 0, 12, 0.00583, 0.000000218])
X1 = X1.reshape(1, -1)
x_train, x_test, y_train, y_test = train_test_split(X, y2, train_size=0.80)
abd = AdaBoostRegressor(DecisionTreeRegressor(
    max_depth=10), n_estimators=900, random_state=123)
abd.fit(X, y1)
y_ans2 = abd.predict(X1)
# print("the score of try2 is: "+str(abd.score(X, y1)))
abd.fit(X, y2)
y_ans5 = abd.predict(X1)
# print(" and the score of try5 is: "+str(abd.score(X, y2)))

print(y_ans2, y_ans5)


# # #
# # # 以上模型已经给出try2，try5#


def backtrylottary(try2, try5):
    try3 = 0.24969979*try2-1.03537551*try5+45.75397189052691
    try6 = 0.10733752*try2-0.42794191*try5-1.03302939*try3+44.50066373640635
    try4 = -0.83922811*try2 + 0.23367546*try5 - \
        0.07531399*try3-1.13885968*try6+47.119830500500385
    try7 = -0.9928097*try2-0.96144148*try5-0.88078448*try3 - \
        0.77547076*try6-0.85302574*try4+88.34079679557357
    if try2+try3+try4+try5+try6+try7 >= 100:
        try2 -= try2*(try2+try3+try4+try5+try6+try7-100)/100
        try3 -= try3*(try2+try3+try4+try5+try6+try7-100)/100
        try4 -= try4*(try2+try3+try4+try5+try6+try7-100)/100
        try5 -= try5*(try2+try3+try4+try5+try6+try7-100)/100
        try6 -= try6*(try2+try3+try4+try5+try6+try7-100)/100
        try7 -= try7*(try2+try3+try4+try5+try6+try7-100)/100
        try1 = 0
    else:
        try1 = 100-(try2+try3+try4+try5+try6+try7)
    return try1, try3, try4, try6, try7


print(backtrylottary(y_ans2, y_ans5))


y_ans1 = []
y_ans3 = []
y_ans4 = []
y_ans6 = []
y_ans7 = []
temp1 = 0
temp2 = 0
temp3 = 0
temp4 = 0
temp5 = 0
for i in range(0, 355):
    temp1, temp2, temp3, temp4, temp5 = backtrylottary(y_ans2[i], y_ans5[i])
    y_ans1.append(temp1)
    y_ans3.append(temp2)
    y_ans4.append(temp3)
    y_ans6.append(temp4)
    y_ans7.append(temp5)

data3 = {
    '1': y_ans1,
    '2': y_ans2,
    '3': y_ans3,
    '4': y_ans4,
    '5': y_ans5,
    '6': y_ans6,
    '7': y_ans7
}
df22 = pd.DataFrame(data3)
df22.to_csv('predict.csv')

t1, t2, t3, t4, t5, t6, t7 = backtrylottary(y_ans2, y_ans5)
print(t1, t2, t3, t4, t5, t6, t7)

X1 = np.array([[0, 12, 0.00583, 0.000000218, 124000000]])
df19 = pd.read_csv('data1.csv')
X = df19.iloc[:, 8:13].values
y = (df19['2_tries']+df19['3_tries']).values
y_md = np.median(y)
z = (df19['5 tries']+df19['6 tries']).values
w = df19['4 tries']/(df19['7 or more tries (X)']+1)
sc = StandardScaler()
X = sc.fit_transform(X)
# print(y2.dtype)
s = []
for j in range(4, 10):
    for i in range(100, 500, 100):
        abd = AdaBoostRegressor(DecisionTreeRegressor(
            max_depth=j), n_estimators=i, random_state=114)
        abd.fit(X, y)
        s.append(abd.score(X, y)-0.2)
print(s)
y2 = abd.predict(X)
y2_md = np.median(y)
df23 = pd.DataFrame(data=s, columns=['score'])
df23.to_csv('df23.csv')
temp = 0
for i in range(0, 355):
    if (y[i]-y_md)*(y2[i]-y2_md) < 0:
        temp += 1
print(temp)
if abd.predict(X) > np.median(y):
    print("It's a Easy2Guess word!")
else:
    print("It's a Hard2Guess word!")


abd.fit(X, z)
if abd.predict(X) > np.median(z):
    print("It's a Need2Reason word!")
else:
    print("It's a Hard2Reason word!")


abd.fit(X, w)
if abd.predict(X) > np.median(w):
    print("It's easy!")
else:
    print("It's hard!")
