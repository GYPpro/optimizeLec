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
实验项目名称#underline[#text("       求一维函数最小值      ")]指导老师#underline[#text("   吴乐秦   ")]\
实验项目编号#underline[#text("       2     ")]实验项目类型#underline[#text("  设计性  ")]实验地点#underline[#text(" 数学系机房 ")]\
学生姓名#underline[#text("            郭彦培            ")]学号#underline[#text("            2022101149               ")]\
学院#underline[#text(" 信息科学技术学院 ")]系#underline[#text(" 数学系 ")]专业#underline[#text(" 信息管理与信息系统 ")]\
实验时间#underline[#text(" 2024年4月15日上午 ")]#text("~")#underline[#text("4月18日晚上")] 温度#underline()[33]℃湿度#underline()[95%]\
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
 实现利用迭代方法计算一维函数最小值的自定义函数。函数能处理最基本的异常，并比较这些方法在收敛速度上的表现。

= *实验原理与理论分析*

本次实验选用*最速下降法*，*牛顿法*和*割线法*。
== 最速下降法

对于当前搜索点$x_k$，有梯度$d_k = -gradient f(x_k)$。取合适的步长因子$alpha_k s.t. f(x_k + alpha_k d_k) < f(x_k)$ 则$ x_(k+1) = x_k + alpha_k d_k $ 

== 牛顿法
对于二次可微函数$f(x)$，取二次Taylor展开$ f(x_k + s) approx q(k)(s) = f(x_k) + gradient f(x_k)^T s + 1/2 s^T gradient^2 f(x_k) s $
将上式右侧极小化，有迭代方程
$ x_(k+1) = x_k - [gradient^2 f(x_k)]^(-1) gradient f(x_k) $

== 割线法

利用两次迭代值$x_k$，$x_(k-1)$在导函数图像上与x轴形成的交点作为新的迭代点，近似替代牛顿法中导函数的作用，即$ x_(k+1) = x_k - (x_k - x_(k-1)) / (gradient f(x_n) - gradient f(x_(n-1))) gradient f(x_n) $

#pagebreak()

= *代码框架*
\

= *核心代码构成*
#strong()[完整代码见7.附录]
\

= *正确性测试*
\
#strong()[完整测试代码见7.附录]
#h(1.8em)

== 测试数据准备


== 测试结果
\
#h(1.8em)

= *各方法不同情况下的性能表现与分析*
\
#strong()[完整测试代码见7.附录]

== 对于 ：
\
#h(1.8em)

=== 测试结果猜想：
\
#h(1.8em)

=== 测试过程：
\

=== 测试分析：
\
#h(1.8em)

== 对于：
\
#h(1.8em) 

=== 测试结果猜想：
\
#h(1.8em)

=== 测试过程：
\
=== 测试分析：
\
#h(1cm)

== 测试结果总结
\
#h(1.8em)


= *附录*

== 代码

== 仓库
#h(1cm)
#align(center)[
全部代码、与x86可执行程序均同步在本人的`github`：

`https://github.com/GYPpro/optimizeLec`

本次实验报告存放在`/WEE2`文件夹下]
#set text(fill:gray)

#align(bottom)[声明：本实验报告所有代码与测试均由本人独立完成，修改和commit记录均在repo上公开。]