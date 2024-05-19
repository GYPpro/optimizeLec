#set text(font:("Times New Roman","Source Han Serif SC"))
#show raw.where(block: false): box.with(
  fill: luma(240),
  inset: (x: 3pt, y: 0pt),
  outset: (y: 3pt),
  radius: 2pt,
)
#show raw: set text(
    size:12pt,
    font: ("consolas", "Source Han Serif SC")
  )
// Display block code in a larger block
// with more padding.
#show raw.where(block: true): block.with(
  fill: luma(240),
  inset: 10pt,
  radius: 4pt,
)

#set math.equation(numbering: "(1)")

#set text(
    font:("Times New Roman","Source Han Serif SC"),
    style:"normal",
    weight: "regular",
    size: 13pt,
)

#set page(
  paper:"a4",
  number-align: right,
  margin: (x:2.54cm,top:4cm,bottom:2cm),
  header: [
    #set text(
      size: 25pt,
      font: "KaiTi",
    )
    #align(
      bottom + center,
      [ #strong[暨南大学本科实验报告专用纸] ]
    )
    #line(start: (0pt,-5pt),end:(453pt,-5pt))
  ]
)


#text(
  font:"KaiTi GB2312",
  size: 15pt
)[
课程名称#underline[#text("                      运筹学                      ")]成绩评定#underline[#text("                      ")]\
实验项目名称#underline[#text("       求二元函数极小值      ")]指导老师#underline[#text("   吴乐秦   ")]\
实验项目编号#underline[#text("       3     ")]实验项目类型#underline[#text("  设计性  ")]实验地点#underline[#text(" 数学系机房 ")]\
学生姓名#underline[#text("            郭彦培            ")]学号#underline[#text("            2022101149               ")]\
学院#underline[#text(" 信息科学技术学院 ")]系#underline[#text(" 数学系 ")]专业#underline[#text(" 信息管理与信息系统 ")]\
实验时间#underline[#text(" 2024年5月17日上午 ")]#text("~")#underline[#text("5月19日晚上")] 温度#underline()[33]℃湿度#underline()[95%]\
]
#set heading(
  numbering: "1.1."
  )
  
#set par( first-line-indent: 1.8em)

#outline(
  title:[#smallcaps("目录")\ #h(1fr)],
  depth: 2,
);
#set page(  header: [
    #set text(
      size: 25pt,
      font: "KaiTi",
    )
    #align(
      bottom + center,
      [ #strong[暨南大学本科实验报告专用纸(附页)] ]
    )
    #line(start: (0pt,-5pt),end:(453pt,-5pt))
  ])
= *实验目的*
\
 实现利用迭代方法计算二元函数极小值的自定义函数。函数能处理最基本的异常，并比较这些方法在收敛速度上的表现。

= *实验原理与理论分析*

本次实验选用*最速下降法*和*共轭梯度法*
== 最速下降法

对于当前搜索点$x_k$，有梯度$d_k = -gradient f(x_k)$。取合适的步长因子$alpha_k s.t. f(x_k + alpha_k d_k) < f(x_k)$ 则$ x_(k+1) = x_k + alpha_k d_k $ 

== 共轭梯度法



#pagebreak()

= *代码框架*
#h(1.8em)编码利用`C++`完成，遵循`C++17`标准

规定命名空间`lineSearch`内的函数原型

```cpp
	std::pair<double,double> find_mininum(
		double (*func)(double x),  // 原函数
		double (*dfunc)(double x), // 一阶导函数
		double l = -_inf,				   // 下界
		double r = _inf,				   // 上界
		double acc = _acc,				 // 搜索精度
    double x = 0.0,            // 初始点
		int mod = DESCENT				   // 搜索方法
		double (*ddfunc)(double x) = nullptr,// 二阶导函数(可选)
	)
```

#h(1.8em)其中:
// ，`func`为目标函数`dfunc`,`ddfunc`分别为一、二阶导函数，`l`、`r`分别为初始区间的两个端点，`acc`为搜索精度，`x`，`mod`为模式选择。

#figure(
    table(
        [*参数*],[*用途*],[*默认值*],
        [`func`],[目标优化函数],[无，必须提供],
        [`dfunc`],[目标函数一阶导],[无，必须提供],
        [`ddfunc`],[目标函数二阶导],[空函数],
        [`l`],[函数下界],[$10^299$],
        [`r`],[函数上界],[$-10^299$],
        [`acc`],[搜索精度],[$10^(-3)$],
        [`x`],[初始搜索点],[0],
        [`mod`],[搜索模式],[`DESCENT`（最速下降法）],
        columns: 3
    )
)

#h(1.8em)返回值为一个`std::pair<double,double>`类型对象，分别存储了搜索到的$x_(k m)$与对应的最小函数值$f_min$

关于模式选择，命名空间`ODSearch`内提供了三个可选模式：

#figure(
    table(
        [`DESCENT`],[#h(1cm)最速下降法#h(1cm)],
        [#h(1cm)`NEWTON`#h(1cm)],[牛顿法],
        [`SECANT`],[割线法],
        columns: 2
    )
)
#pagebreak()
#h(1cm) 当参数不合法时，程序会抛出异常，并返回固定值`-1`：

#figure(
    table(
        [`Illegal Range Execption`],[#h(1cm)区间不合法#h(1cm)],
        [`Illegal Initial Value`],[#h(1cm)不合法的初始搜索点#h(1cm)],
        [`Derivative Function NOT Provided`],[#h(1cm)选择牛顿法时未提供二阶导#h(1cm)],
        [`Unexpection Search Mod Exception`],[未知的搜索模式],
        [`Unknown Exception`],[其他预料外错误],
        columns: 2
    )
)

#h(1cm)以下是一些函数调用例子：
```cpp
auto ans = ODSearch::find_mininum(f, df, l, r, acc, 0.0, ODSearch::DESCENT);
//用最速下降法进行搜索
lineSearch::find_mininum(f,df,114,514,0.0019,0.0,lineSearch::SECANT, ddf)
//用割线法搜索函数f的[114,514]区间，从初始值x出发，精度为0.0019
```

= *核心代码构成*
#strong()[完整代码见7.附录]

== 最速下降法
```cpp
			double alpha = 0.1;//初始步长因子
			double curx = x;//当前搜索点
			double fmin = func(x);//当前函数值最小值
			double grad = dfunc(x);//当前梯度

			while(abs(grad) > acc)
			{
				//二分线性搜索确定可选步长因子
				while(!(func(curx - alpha * grad) < func(curx)))
					alpha = alpha / 2.0;
				fmin = func(curx - alpha * grad);
				curx -= alpha * grad;
				grad = dfunc(curx);
				alpha = 0.1;
			}
			return {curx,fmin};
```

#pagebreak()

== 牛顿法

```cpp
			/*
			 *@brief 计算近似二阶泰勒的 build in lambda function 
			*/
			auto Taylor = [&](double xk) -> double
			{
				return dfunc(xk) / (ddfunc(xk) * ddfunc(xk));
			};

			double curx = x;//当前搜索点
			double fmin = func(x);//当前函数值最小值
			double grad = dfunc(x);//当前梯度

			while(abs(grad) > acc)
			{
				fmin = func(curx - Taylor(curx));
				curx -= Taylor(curx);
				grad = dfunc(curx);
			}
			return {curx,fmin};
```

\

== 割线法

```cpp
			double curx = x;//当前搜索点
			double prfx = (l + x)/ 2.0;//上一个搜索点
			double fmin = func(x);//当前函数值最小值
			double grad = dfunc(x);//当前梯度

			/*
			 *@brief 计算替代二阶导的割线斜率的 build in lambda function 
			*/
			auto getSec = [&]() -> double{
				return (curx - prfx) * dfunc(curx) / (dfunc(curx) - dfunc(prfx));
			};


			while(abs(grad) > acc)
			{
				fmin = func(curx - getSec());
				curx -= getSec();
				grad = dfunc(curx);
			}
			return {curx,fmin};

```

= *正确性测试*
\
#strong()[见附录]`TOFtest.cpp`
#h(1.8em)

== 测试数据准备

#h(1.8em)测试用的目标函数为一个在`x`轴平移了`dev`的二次函数，即：
```cpp
double dev = 0.03; // deviation
double f(double a)
{
    return (a - dev) * (a - dev);
}
```

#h(1.8em)测试程序将随机生成一系列的偏移值`dev`，和对应的合法搜索区间`l`,`r`、准确度`acc`，并分别调用
```cpp
ODSearch::find_mininum(f,df,l,r,acc,0.0, ODSearch::DESCENT);
ODSearch::find_mininum(f,df,l,r,acc,0.0, ODSearch::NEWTON, ddf);
ODSearch::find_mininum(f,df,l,r,acc,0.0, ODSearch::SECANT, ddf);
```
#h(1.8em)随后分析并输出结果。

规定理论值为`thn`，当前答案为`ans`

下面是10次测试的结果，其中当前精准度$ "acc"_"当前"= "acc" / abs("thn" - "ans") times 100 % $#h(1.8em)反映了搜索的准确度。其中偏差量$ "dev" = max(0,abs("thn"-"ans")-"acc")/"acc" times 100% $#h(1.8em)反应了搜索结果与目标的偏差是否在可接受范围内。

$"acc" > 100%$且$"dev" = 0$时可以视为解是可接受的。

#pagebreak()

== 测试结果
\
#h(1.8em)

#h(1.8em)

#pagebreak()

= *各方法不同情况下的性能表现与分析*
\
#strong()[完整测试代码见7.附录]


== 对于复杂目标函数进行搜索：
#strong()[见附录]`CMFtest.cpp`
\
#h(1.8em)


=== 测试过程：
\
#h(1.8em)

=== 测试分析：
\
#h(1.8em)



== 对于简单函数的快速搜索：
#strong()[见附录]`LGNtest.cpp`
\

#h(1.8em)
=== 测试过程：
\
#h(1.8em) 
=== 测试分析：
\
#h(1.8em)
#pagebreak()

= *附录*

== 代码

=== 核心`core.h`



=== 测试代码

==== `TOFtest.cpp`


==== `CMFtest.cpp`


==== `LGNtest.cpp`


== 仓库
#h(1cm)
#align(center)[
全部代码、与x86可执行程序均同步在本人的`github`：

`https://github.com/GYPpro/optimizeLec`

本次实验报告存放在`/WEE2`文件夹下]
#set text(fill:gray)

#align(bottom)[声明：本实验报告所有代码与测试均由本人独立完成，修改和commit记录均在repo上公开。]