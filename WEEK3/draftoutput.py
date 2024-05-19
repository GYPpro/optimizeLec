# %%
import matplotlib.pyplot as plt
import numpy as np

# 读取文件中的坐标点
def read_points(filename):
    with open(filename, 'r') as file:
        points = [tuple(map(float, line.strip().split(' '))) for line in file.readlines()]
    return points

def f(x, y):
    return (x-0.5)**2 + 0.5*(y-0.5)**2

# 绘制等值线
def plot_contour(ax, function, x_range, y_range, levels):
    X, Y = np.meshgrid(np.linspace(x_range[0], x_range[1], 100), np.linspace(y_range[0], y_range[1], 100))
    Z = function(X, Y)
    contour = ax.contour(X, Y, Z, levels)
    ax.clabel(contour, inline=True, fontsize=10)
    return contour

# 主函数
    # 读取坐标点
points1 = read_points('GD.log')
points2 = read_points('CG_FR.log')
points3 = read_points('CG_PRP.log')

# 创建图形和轴
fig, ax = plt.subplots()

# 绘制折线图
ax.plot([p[0] for p in points1], [p[1] for p in points1], label='GD', color='blue',marker='o')
ax.plot([p[0] for p in points2], [p[1] for p in points2], label='CG(FR)', color='red',marker='+')
ax.plot([p[0] for p in points3], [p[1] for p in points3], label='CG(PRP)', color='green',marker='x')
# ax.plot(0.5,0.5,marker='o',color='red',label='min point')

# 绘制等值线，例如 y = x^2
contour = plot_contour(ax,f, (0, 0.7), (0, 0.7), [x/20 for x in range(0, 20, 1)])

# 设置图例
ax.legend()

# 设置坐标轴范围
# ax.set_xlim(0, 1)
# ax.set_ylim(0, 1)

# 显示图形
ax.set_aspect('equal')
plt.show()


# %%
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['STZhongsong']
# 准备数据
values = [104, 14, 23]  # 要比较的数字
labels = ['GD', 'CG(FR)', 'CG(PRP)']  # 每个数字的标签

# 创建条形图
plt.bar(labels, values)

# 设置图表标题和轴标签
plt.title('迭代次数对比')
plt.xlabel('Labels')
plt.ylabel('Values')

# 显示值标签在每个条形上
for i, v in enumerate(values):
    plt.text(i, v + 1, str(v), ha='center')

# 显示图表
plt.show()

# %%
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['STZhongsong']
# 准备数据
values = [1.142,0.188,0.336]  # 要比较的数字
labels = ['GD', 'CG(FR)', 'CG(PRP)']  # 每个数字的标签

# 创建条形图
plt.bar(labels, values)

# 设置图表标题和轴标签
plt.title('时间消耗对比')
plt.xlabel('Labels')
plt.ylabel('Values')

# 显示值标签在每个条形上
for i, v in enumerate(values):
    plt.text(i, v + 0.005, str(v), ha='center')

# 显示图表
plt.show()

# %% [markdown]
# 

# %%
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 设置常数
a = 1
b = 3

# 创建x和y的网格
x = np.linspace(-0.5, 1.5, 400)
y = np.linspace(-0.5, 1.5, 400)
X, Y = np.meshgrid(x, y)

# 计算Rosenbrock函数的值
Z = (a - X)**2 + b * (Y - X**2)**2

# 创建3D图像
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# 绘制3D曲面图
surf = ax.plot_surface(X, Y, Z, cmap='viridis')
# 标记最小值点
min_x = 1
min_y = 1
min_z = 0  # Rosenbrock函数的最小值


# 添加颜色条
fig.colorbar(surf)

# 设置图表标题和轴标签
ax.set_title('3D Surface of Rosenbrock Function')
ax.set_xlabel('X axis')
ax.set_ylabel('Y axis')
ax.set_zlabel('Z axis')
ax.view_init(elev=20, azim=5)

ax.scatter([min_x], [min_y], [min_z], color='black')  # 标记最小值点
# ax.text(min_x, min_y, min_z, 'Min', color='black', fontsize=12)
# 显示图像
plt.show()

# %%
import matplotlib.pyplot as plt
import numpy as np
import math as mt


# 读取文件中的坐标点
def read_points(filename):
    with open(filename, 'r') as file:
        points = [tuple(map(float, line.strip().split(' '))) for line in file.readlines()]
    return points

def f(x, y):
    return (a - x)**2 + b * (y - x**2)**2

# 绘制等值线
def plot_contour(ax, function, x_range, y_range, levels):
    X, Y = np.meshgrid(np.linspace(x_range[0], x_range[1], 100), np.linspace(y_range[0], y_range[1], 100))
    Z = function(X, Y)
    contour = ax.contour(X, Y, Z, levels)
    ax.clabel(contour, inline=True, fontsize=10)
    return contour

# 主函数
    # 读取坐标点
points1 = read_points('GD.log')
points2 = read_points('CG_FR.log')
points3 = read_points('CG_PRP.log')

# 创建图形和轴
fig, ax = plt.subplots()

# 绘制折线图
ax.plot([p[0] for p in points1], [p[1] for p in points1], label='GD', color='blue',marker='o')
ax.plot([p[0] for p in points2], [p[1] for p in points2], label='CG(FR)', color='red',marker='+')
ax.plot([p[0] for p in points3], [p[1] for p in points3], label='CG(PRP)', color='green',marker='x')
# ax.plot(1,1,marker='o',color='red',label='min point')

# 绘制等值线，例如 y = x^2
contour = plot_contour(ax,f, (-0.5, 1.5), (-0.5, 1.5), [(x/6)**2.5 for x in range(0, 20, 1)])

# 设置图例
ax.legend()

# 设置坐标轴范围
# ax.set_xlim(0, 1)
# ax.set_ylim(0, 1)

# 显示图形
ax.set_aspect('equal')
plt.show()


# %%
f(0,0)

# %%
f(0.01,0.03)

# %%
f(0.05,0.15)

# %%
f(0.0501,0.1505) - f(0.05,0.15)

# %%
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['STZhongsong']
# 准备数据
values = [444, 316, 313]  # 要比较的数字
labels = ['GD', 'CG(FR)', 'CG(PRP)']  # 每个数字的标签

# 创建条形图
plt.bar(labels, values)

# 设置图表标题和轴标签
plt.title('迭代次数对比')
plt.xlabel('Labels')
plt.ylabel('Values')

# 显示值标签在每个条形上
for i, v in enumerate(values):
    plt.text(i, v + 1, str(v), ha='center')

# 显示图表
plt.show()

# %%
import numpy as np
import matplotlib.pyplot as plt

# Rosenbrock函数
def rosenbrock(x, y):
    a = 1
    b = 3
    return (a - x)**2 + b * (y - x**2)**2

# 从文件中读取坐标
def read_coordinates(filename):
    with open(filename, 'r') as file:
        points = [tuple(map(float, line.strip().split(' '))) for line in file.readlines()]
    return points

# 绘制函数值
def plot_rosenbrock_values(points, label,_marker):
    values = [rosenbrock(x, y) for x, y in points]
    plt.plot([i for i in range(len(points))], values, label=label, marker=_marker,markersize=0)

# 主函数
def main():
    # 读取三组坐标
    points1 = read_points('GD.log')
    points2 = read_points('CG_FR.log')
    points3 = read_points('CG_PRP.log')
    
    # points1 = points1[1:len(points1):3]
    # points2 = points2[1:len(points2):3]
    # points3 = points3[1:len(points3):3]

    # 计算Rosenbrock函数值并绘制
    plt.figure(figsize=(10, 6))
    plot_rosenbrock_values(points1, 'GD','o')
    plot_rosenbrock_values(points2, 'CG_FR','+')
    plot_rosenbrock_values(points3, 'CG_PRP','x')
    print(points1)
    # 添加图例
    plt.legend()
    
    # 添加标题和轴标签
    plt.title('Rosenbrock Function Values for Coordinates in Each Iteration')
    plt.xlabel('Each Iteration')
    plt.ylabel('Rosenbrock Function Value')
    
    plt.yscale('log')

    # 显示网格
    plt.grid(True)
    
    # 显示图像
    plt.show()

if __name__ == '__main__':
    main()

# %%



