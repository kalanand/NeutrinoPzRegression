__        ___           _     _       _ _     ___ 
\ \      / / |__   __ _| |_  (_)___  (_) |_  |__ \
 \ \ /\ / /| '_ \ / _` | __| | / __| | | __|   / /
  \ V  V / | | | | (_| | |_  | \__ \ | | |_   |_| 
   \_/\_/  |_| |_|\__,_|\__| |_|___/ |_|\__|  (_) 
                                                  
Reconstruction of missing features in data using regression 
===========================================================

We often encounter situations where no data value is stored for a 
particular variable in an observation. A familiar example in 
particle physics is the decay of the W boson to a lepton (e.g., 
electron or muon) and a neutrino, where the latter escapes largely 
undetected. We only measure the transverse component of the missing 
energy in the detector, which signifies the presence of the neutrino. 
Even this quantity is measured with limited precision and large 
statistical uncertainty. The longitudinal component remains 
completely undetected. Technical aspects of the problem are described 
in the following slides

https://github.com/kalanand/NeutrinoPzRegression/raw/master/README.pdf


The slides also describe a regression analysis to reconstruct the 
missing feature, i.e., the longitudinal component of the neutrino 
energy.  

Turns out that this particular problem can also be solved analytically 
if one makes a crucial simplification that the W boson mass is always 
exactly equal to its mean value 80.40 GeV. However, this assumption 
leads to a quadratic equation for the neutrino longitudinal energy, 
whose solutions are sometimes imaginary/unphysical. This causes serious 
problems for analyzing the data, e.g., in reconstructing the decays of 
the Higgs boson. Since regression never predicts imaginary solution, its 
predictions do not suffer from the same problem. In addition, the 
solution provided by regression analysis turns out to be unbiased and 
better behaved in the most extreme kinematic regimes.

 _____           _                     _                 _ 
|_   _|__     __| | _____      ___ __ | | ___   __ _  __| |
  | |/ _ \   / _` |/ _ \ \ /\ / / '_ \| |/ _ \ / _` |/ _` |
  | | (_) | | (_| | (_) \ V  V /| | | | | (_) | (_| | (_| |
  |_|\___/   \__,_|\___/ \_/\_/ |_| |_|_|\___/ \__,_|\__,_|
                                                           

git clone git://github.com/kalanand/NeutrinoPzRegression


 _   _                 _                           
| | | | _____      __ | |_ ___    _ __ _   _ _ __  
| |_| |/ _ \ \ /\ / / | __/ _ \  | '__| | | | '_ \ 
|  _  | (_) \ V  V /  | || (_) | | |  | |_| | | | |
|_| |_|\___/ \_/\_/    \__\___/  |_|   \__,_|_| |_|
                                                   
                                                   
The training and validation are performed by running the script 
'TMVARegression.C'. Application of the regression result to predict the 
W and Higgs boson masses are shown in the script 'makeplots.C'. All other 
files in the repository are auxiliary. Both scripts can be run interactively 
from a ROOT session (http://root.cern.ch) or as compiled binaries. 


 _____         _           _           _       _      _        _ _     
|_   _|__  ___| |__  _ __ (_) ___ __ _| |   __| | ___| |_ __ _(_) |___ 
  | |/ _ \/ __| '_ \| '_ \| |/ __/ _` | |  / _` |/ _ \ __/ _` | | / __|
  | |  __/ (__| | | | | | | | (_| (_| | | | (_| |  __/ || (_| | | \__ \
  |_|\___|\___|_| |_|_| |_|_|\___\__,_|_|  \__,_|\___|\__\__,_|_|_|___/
                                                                       
                                    
Author : Kalanand Mishra
Home Page : https://github.com/kalanand/NeutrinoPzRegression
Operating System : OS Independent
Programming Language : C++ 
Intended Audience : Science/Research


 _     _                         
| |   (_) ___ ___ _ __  ___  ___ 
| |   | |/ __/ _ \ '_ \/ __|/ _ \
| |___| | (_|  __/ | | \__ \  __/
|_____|_|\___\___|_| |_|___/\___|
                                 
NeutrinoPzRegression is a free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as published 
by the Free Software Foundation; either version 3 of the License or any 
later version: <http://www.gnu.org/licenses/>. This software is distributed 
WITHOUT ANY WARRANTY. 
