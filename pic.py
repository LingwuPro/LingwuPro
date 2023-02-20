import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# df1 = pd.read_csv('newdata.csv')
# # print(df1.head())
# x = df1['Contest number'].values
# y = 1.921e05*np.exp(-((x-26.94)/22.21)**2)+1.418e05 * \
#     np.exp(-((x-57.82)/48.04)**2)+4.954e04*np.exp(-((x-125.7)/216.3)**2)
# z = df1['Number of  reported results'].values

# data1 = {
#     'X': x,
#     'func': y,
#     'real': z
# }
# df2 = pd.DataFrame(data1)
# # print(df2)
# # 条形图
# # 绘制基础图层
# fig, ax1 = plt.subplots(figsize=(10, 6))
# color = 'tab:green'
# ax1.set_title('Average Percipitation Percentage by Month', fontsize=16)
# #ax1.set_xlabel('Month', fontsize=16)
# ax1.set_ylabel('Avg Temp', fontsize=16, color=color)

# # 第一图条形图
# ax1 = sns.barplot(x='X', y='real', data=df2, palette='summer')
# ax1.tick_params(axis='y')
# # twinx共享x轴(类似的语法，如共享y轴twiny)
# ax2 = ax1.twinx()
# color = 'tab:red'
# # 第二个图，折线图
# ax2.set_ylabel('Avg Percipitation %', fontsize=16, color=color)
# ax2 = sns.lineplot(x='X', y='func', data=df2, sort=False, color=color)
# ax2.tick_params(axis='y', color=color)
# sns.despine()
# # 显示绘制结果
# plt.show()

# df3 = pd.read_csv('data.csv')
# x = df3['Contest number'].values
# y = df3['2_tries'].values
# z = df3['2'].values
# z = z-y
# # z = 1/(1.372452e-7*(x+3)-7.497738e-8)

# data2 = {
#     'X': x,
#     'Y': y,
#     'Z': z
# }
# df4 = pd.DataFrame(data2)

# fig, ax1 = plt.subplots(figsize=(10, 6))
# color = 'tab:green'
# #ax1.set_title('', fontsize=16)
# #ax1.set_xlabel('Month', fontsize=16)
# ax1.set_ylabel('Avg Temp', fontsize=16, color=color)

# # 第一图条形图
# ax1 = sns.barplot(x='X', y='Y', data=df4, palette='summer')
# ax1.tick_params(axis='y')
# # twinx共享x轴(类似的语法，如共享y轴twiny)
# ax2 = ax1.twiny()
# color = 'tab:red'
# # 第二个图，折线图
# ax2.set_ylabel('Avg Percipitation %', fontsize=16, color=color)
# ax2 = sns.lineplot(x='X', y='Z', data=df4, sort=False, color=color)
# ax2.tick_params(axis='y', color=color)
# sns.despine()
# # 显示绘制结果
# plt.show()
font = {'family': 'Arial'  # 'serif',
        #         ,'style':'italic'
        , 'weight': 'bold'  # 'normal'
        #         ,'color':'red'
        , 'size': 0
        }

df4 = pd.read_csv('data.csv')

"""
    批量绘制box分布图形， 适用于分类标签的不同指标值的分布数据查看， 对于指标值很多的时候比较适用
    df : DataFrame数据
    lst : 需要绘制图形的字段
    """
sns.set()
fig = plt.figure(figsize=(36, 30))  # 这里的画布大小还是先设置好吧。

# 遍历每张子图
ax = fig.add_subplot(7, 1, 1)
ax1 = sns.lineplot(x='_', y='1_try',
                   data=df4, sort=False, color='#7C9971')
plt.xticks([])
ax2 = ax1.twiny()
ax2 = sns.lineplot(x='_', y='1', data=df4,
                   sort=False, color='#34F40A', linestyle='--')
# 单独设置了每个子图的标题， 为了方便查看， 也可以省略
# ax.set_title('try1'+'_index_contrast')
# 设置子图之间的横纵边距， 不然会挤到一块， 影响阅读
plt.subplots_adjust(wspace=0.3, hspace=0.6)
plt.tick_params(axis='x', width=0)
plt.xticks([])
# plt.legend(prop=font)


ax = fig.add_subplot(7, 1, 2)
ax1 = sns.lineplot(x='_', y='2_tries',
                   data=df4, sort=False, color='#7C9971')
plt.xticks([])

ax2 = ax1.twiny()
ax2 = sns.lineplot(x='_', y='2', data=df4,
                   sort=False, color='#34F40A', linestyle='--')
# 单独设置了每个子图的标题， 为了方便查看， 也可以省略
# ax.set_title('try2'+'_index_contrast')
plt.xticks([])

plt.subplots_adjust(wspace=0.3, hspace=0.6)
plt.tick_params(axis='x', width=0)


# 设置子图之间的横纵边距， 不然会挤到一块， 影响阅读

ax = fig.add_subplot(7, 1, 3)
ax1 = sns.lineplot(x='_', y='3_tries',
                   data=df4, sort=False, color='#7C9971')
plt.xticks([])

ax2 = ax1.twiny()
ax2 = sns.lineplot(x='_', y='3', data=df4,
                   sort=False, color='#34F40A', linestyle='--')
# 单独设置了每个子图的标题， 为了方便查看， 也可以省略
# ax.set_title('try1'+'_index_contrast')
# 设置子图之间的横纵边距， 不然会挤到一块， 影响阅读
plt.xticks([])

plt.subplots_adjust(wspace=0.3, hspace=0.6)
plt.tick_params(axis='x', width=0)


ax = fig.add_subplot(7, 1, 4)
ax1 = sns.lineplot(x='_', y='4_tries',
                   data=df4, sort=False, color='#7C9971')
plt.xticks([])
ax2 = ax1.twiny()
ax2 = sns.lineplot(x='_', y='4', data=df4,
                   sort=False, color='#34F40A', linestyle='--')
plt.xticks([])
# 单独设置了每个子图的标题， 为了方便查看， 也可以省略
# ax.set_title('try1'+'_index_contrast')
# 设置子图之间的横纵边距， 不然会挤到一块， 影响阅读
plt.subplots_adjust(wspace=0.3, hspace=0.6)
plt.tick_params(axis='x', width=0)


ax = fig.add_subplot(7, 1, 5)
ax1 = sns.lineplot(x='_', y='5_tries',
                   data=df4, sort=False, color='#7C9971')
sns.despine(top=True, right=True, left=True, bottom=True)
plt.xticks([])
ax2 = ax1.twiny()
ax2 = sns.lineplot(x='_', y='5', data=df4,
                   sort=False, color='#34F40A', linestyle='--')
sns.despine(top=True, right=True, left=True, bottom=True)

# 单独设置了每个子图的标题， 为了方便查看， 也可以省略
# ax.set_title('try1'+'_index_contrast')
# 设置子图之间的横纵边距， 不然会挤到一块， 影响阅读
plt.xticks([])
plt.subplots_adjust(wspace=0.3, hspace=0.6)
plt.tick_params(axis='x', width=0)


ax = fig.add_subplot(7, 1, 6)
ax1 = sns.lineplot(x='_', y='6_tries',
                   data=df4, sort=False, color='#7C9971')
plt.xticks([])
ax2 = ax1.twiny()
ax2 = sns.lineplot(x='_', y='6', data=df4,
                   sort=False, color='#34F40A', linestyle='--')
plt.xticks([])
# 单独设置了每个子图的标题， 为了方便查看， 也可以省略
# ax.set_title('try1'+'_index_contrast')
# 设置子图之间的横纵边距， 不然会挤到一块， 影响阅读
plt.subplots_adjust(wspace=0.3, hspace=0.6)
plt.tick_params(axis='x', width=0)


ax = fig.add_subplot(7, 1, 7)
ax1 = sns.lineplot(x='_', y='X',
                   data=df4, sort=False, color='#7C9971')
plt.xticks([])
ax2 = ax1.twiny()
ax2 = sns.lineplot(x='_', y='7', data=df4,
                   sort=False, color='#34F40A', linestyle='--')
plt.xticks([])
# 单独设置了每个子图的标题， 为了方便查看， 也可以省略
# ax.set_title('try1'+'_index_contrast')
# 设置子图之间的横纵边距， 不然会挤到一块， 影响阅读
plt.subplots_adjust(wspace=0.3, hspace=0.3)
plt.tick_params(axis='x', width=0)
plt.xticks(fontsize=0)


plt.show()
