# RA-selection-aglorithms
This files correspond to the submitted version of Assignment #2 for Randomized Algorithms course (Master in Innovation and Research in Informatics), Fall 2022

### Author: Irene Simó Muñoz
### Date: November 6th 2022

---------
*Contents*:
- "Report2_ISM.pdf": Report of the assignment in PDF format
- "quickselect.c": C script for Randomized Quickselect experiment
    - ```$ ./quickselect <size_of_array> <j-th_element>```
- "floydrivest.c": C script for Floyd-Rivest (or Randomized Median) experiment
    - ```$ ./floydrivest <size_of_array>```
- "quickselect-median-of-t.c": C script for the Bonus section, Median-of-(2t+1) Quickselect
    - ```$ ./quickselect-median-of-t <size_of_array> <j-th_element>```
- "statisctics.c": C script performing mean and standard deviation computations
    - ```$ ./statistics <path_of_txt_file> <rows> <columns>```
- "compiler": Bash script used to perform multiple runs of the experiments
- "/out": Directory with all needed subdirectories created. Experimental data is not included due to file size management issues.

---------
*Instructions on experiment repetition*:

The experiments can be run with bash script script. The script is provided with all lines commented; uncomment blocks to run experiments. Final results are stored in a "Stats.txt" file inside ```/out``` directory.

---------
*Requirements*:
- C compiler (libraries stdlib.h, stdio.h, math.h, stdbool.h and time.h)
