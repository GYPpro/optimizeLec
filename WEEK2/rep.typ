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
实验项目名称#underline[#text("       求单峰函数最小值      ")]指导老师#underline[#text("   吴乐秦   ")]\
实验项目编号#underline[#text("       1     ")]实验项目类型#underline[#text("  设计性  ")]实验地点#underline[#text(" 数学系机房 ")]\
学生姓名#underline[#text("            郭彦培            ")]学号#underline[#text("            2022101149               ")]\
学院#underline[#text(" 信息科学技术学院 ")]系#underline[#text(" 数学系 ")]专业#underline[#text(" 信息管理与信息系统 ")]\
实验时间#underline[#text(" 2024年3月21日上午 ")]#text("~")#underline[#text("3月23日晚上")] 温度#underline()[21]℃湿度#underline()[85%]\
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
#h(1.8em)基于无导数二分法、黄金分割法和Fibonacci法实现对单谷函数的求解


= *实验原理与理论分析*

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

== 对于复杂目标函数进行搜索：
\
#h(1.8em)这一项测试针对在绝大部分实用数学模型的求解时的场景，即目标函数十分复杂难以计算，需要尽量减少计算函数值的次数，是最主要的应用环境，考察算法解决复杂问题的能力。

=== 测试结果猜想：
\
#h(1.8em)每次迭代搜索次数较少的Fibonacci法与黄金分割法将显著快于虽然下降率大但搜索次数较高二分法。

=== 测试过程：
\

=== 测试分析：
\
#h(1.8em)根据测试结果来看，基本符合预期。二分查找由于大量额外的查找，导致时间消耗高于另外两种搜索，又由于斐波那契法的下降速率略快于黄金分割法，因此最终执行速率略快。

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


== 代码仓库
#h(1cm)
#align(center)[
全部代码、与x86可执行程序均同步在本人的`github`：

`https://github.com/GYPpro/optimizeLec`

本次实验报告存放在`/WEE1`文件夹下]
#set text(fill:gray)

#align(bottom)[声明：本实验报告所有代码与测试均由本人独立完成，修改和commit记录均在repo上公开。]