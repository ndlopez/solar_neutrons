# Solar Neutrons

Data analysis of the Solar-Neutron Telescopes (SNTs) installed at 7 different locations around the world.<br>

Mt.Norikura(JP), Mt. Chacaltaya(BO), Mt. Jungfraujoch (CH), Mt. Sierra Negra(MX), Tibet(CN), Mt.MaunaKea(Us), Mt. Aragats(AM). <br>

The project is a cooperation between Nagoya University, Bern University, Universidad Nacional Aut\'onoma de Mexico, and Universidad Mayor de San Andr\'es.<br>

More info at [Nagoya University:ISEE](https://isee.nagoya-u.ac.jp)

## Data Analysis Tools

1. <arrange_data.cpp> Reads data from SNTs and uniforms in a single format for better analysis. Outputs arranged format file and Plots neutron intensity levels for a set date.

2. <surv_prob.cpp> Calculate the survival probability of neutrons coming from the Sun.<br>
Requires [CERN's ROOT](https://root.cern.ch) (C++ Framework)

3. <Run_Shibata.sh> Runs [Shibata Model Simulation](https://agupubs.onlinelibrary.wiley.com/doi/abs/10.1029/93JA03175) and outputs data

*Environment*: NEC Esprimo Core i3

*OS*: Debian stretch

*Editor*: Emacs

*Data wranglers*: AWK, SED
