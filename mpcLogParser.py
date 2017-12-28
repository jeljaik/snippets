##################### USEFUL FUNCTIONS #########################################
def splitFileBy(regexp, contents):
    result = re.split(regexp, contents)
    del result[0] # First one is always empty
    return result

def extractValue(regexp, input, output):
    result = re.search(regexp, input)
    if (result):
        output.append(result.group(1))
        # print(result.group(1))
    return

def plotOverallError(iterations, key, whichBlockInIteration, whichSubBlock, result):
  counter = 0
  regexValue = "\s+=  (\d+.\d+e(\+|\-)\d+)"
  for it in iterations:
      counter = counter + 1
      # print("ITERATION: "+str(counter))
      blocksInIteration = splitFileBy("\*+\n\*+ .*\n\*+\n", it)
      if len(blocksInIteration) < 5:
          break
      subBlocks = splitFileBy("\n.*:\n", blocksInIteration[whichBlockInIteration])
      extractValue(key+regexValue, subBlocks[whichSubBlock], result)
  return

def plotAcceptablCheckVariable(iterations, variable, whichBlockInIteration, axis, whichSubplot):
    variable_first = []
    variable_second = []
    variable_third = []
    plotOverallError(iterations, variable, whichBlockInIteration, 0, variable_first)
    plotOverallError(iterations, variable, whichBlockInIteration, 1, variable_second)
    plotOverallError(iterations, variable, whichBlockInIteration, 2, variable_third)
    y_variable_first = np.asfarray(variable_first)
    y_variable_second = np.asfarray(variable_second)
    y_variable_third = np.asfarray(variable_third)
    # Plotting
    x = range(len(y_variable_third))
    if (y_variable_first.size != 0):
        axis[whichSubplot].plot(x,y_variable_first, '.-', markersize=5, label="Line search")
    if (y_variable_second.size != 0):
        axis[whichSubplot].plot(x,y_variable_second, '.-', markersize=5, label="Convergence check")
    if (y_variable_third.size != 0):
        axis[whichSubplot].plot(x,y_variable_third, '.', markersize=5, label="aceptable check")
    formatter = mpl.ticker.ScalarFormatter(useMathText=True)
    formatter.set_scientific(True)
    formatter.set_powerlimits((-1,1))
    axis[whichSubplot].yaxis.set_major_formatter(formatter)
    axis[whichSubplot].set_ylabel(variable)
    axis[whichSubplot].legend()

    return

def plotAcceptablCheckVariable2(iterations, variable, whichBlockInIteration, searchInWhichSubBlocks, axis, whichSubplot):
    print(searchInWhichSubBlocks)
    # variables = ['']*len(searchInWhichSubBlocks)
    variables = [[] for _ in searchInWhichSubBlocks]
    count = 0
    for var in variables:
        plotOverallError(iterations, variable, whichBlockInIteration, searchInWhichSubBlocks[count], var)
        count = count + 1
    # print("FINAL OBTAINED LIST IS: ")
    # print(variables)
    # variable_first = []
    # variable_second = []
    # variable_third = []
    # for var in
    # plotOverallError(variable, whichBlockInIteration, 0, variable_first)
    # plotOverallError(variable, whichBlockInIteration, 1, variable_second)
    # plotOverallError(variable, whichBlockInIteration, 2, variable_third)
    y_variable = [[] for _ in searchInWhichSubBlocks]
    count = 0
    # print("yvar before loop")
    # print(y_variable)
    for yvar in y_variable:
        yvar = np.asfarray(variables[count])
        count += 1

    # Plotting
    print("YVAR[O]")
    print(yvar[0])
    # x = range(len(yvar[0]))
    # for y in yvar:
    #     axis[whichSubplot].plot(x,y, '.-', markersize=15, label="")
    #
    # # axis[whichSubplot].plot(x,y_variable_first, '.-', markersize=15, label="Line search")
    # # axis[whichSubplot].plot(x,y_variable_second, '.-', markersize=15, label="Convergence check")
    # # axis[whichSubplot].plot(x,y_variable_third, '.', markersize=15, label="aceptable check")
    # formatter = mpl.ticker.ScalarFormatter(useMathText=True)
    # formatter.set_scientific(True)
    # formatter.set_powerlimits((-1,1))
    # axis[whichSubplot].yaxis.set_major_formatter(formatter)
    # axis[whichSubplot].set_ylabel(variable)
    # axis[whichSubplot].legend()

    return

def plotsForTest(whichTest):
    iterations = splitFileBy("\*+\n\*+ Summary of Iteration: \d+:\n\*+\n", whichTest)
    print("Number of iterations found in first test ")
    print(len(iterations))

    # Split iteration by blocks
    # print(iterations[0])
    blocksInIteration = splitFileBy("\*+\n\*+ .*\n\*+\n", iterations[0])
    print("I found " + str(len(blocksInIteration)) + " blocks in the current iteration")
    # print(blocksInIteration[3])

    # Split block in sub-blocks
    subBlocks = splitFileBy("\n.*:\n", blocksInIteration[3])
    print("I found " + str(len(subBlocks)) + " subblocks in the current block")

    # Preparing figure
    fig, ax = plt.subplots(5, sharex=True)

    ####### Looking for overall_error in the third group of Acceptable Check
    # plotAcceptablCheckVariable("overall_error", 3, ax, 0)
    plotAcceptablCheckVariable(iterations, "overall_error", 3, ax, 0)

    ####### Looking for constr_viol in the third group of Acceptable check
    plotAcceptablCheckVariable(iterations, "constr_viol", 3, ax, 1)

    ####### Looking for dual_inf in the third group of acceptable check
    plotAcceptablCheckVariable(iterations, "dual_inf", 3, ax, 2)

    ####### Looking for compl_if in the third group of acceptable check
    plotAcceptablCheckVariable(iterations, "compl_inf", 3, ax, 3)

    ####### Looking for compl_if in the third group of acceptable check
    plotAcceptablCheckVariable(iterations, "curr_obj_val_", 3, ax, 4)
    # plotAcceptablCheckVariable2(iterations, "curr_obj_val_", 3, (0,2), ax, 4)

    plt.xlabel('Iteration')
    plt.show()

    return


################################################################################
###################### BEGINNING OF THE SCRIPT #################################
################################################################################
import sys
import re
import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter, ScalarFormatter
import numpy as np
plt.style.use('fivethirtyeight')

filename = ['']
# If only the name of the file is given, plot for all test
if len(sys.argv) == 2:
    fileName = sys.argv[1]
# If in addition to th ename of the file, the flag plotAll is given, all tests are plotted
if len(sys.argv) == 3:
    fileName = sys.argv[1]
    if sys.argv[2] == "plotAll"
        plotAll = True

# Read file
f=open(fileName,"r")
if f.mode == "r":
    contents = f.read()

# Split file by tests
tests = splitFileBy("List of options:\n", contents)
print("Number of tests found:")
print(len(tests)) # The first one is empty

####### PROCESSING FOR TEST 1 ##################################################
if plotAll:
    for singleTest in tests:
        plotsForTest(singleTest)

# Otherwise (by default) plot just the last test
print("Plotting only the last test of file: "+filename)
plotsForTest(tests[len(tests)-1])





# # b = re.compile(r"""(?<=  overall_error =  )  # match the following numbers preceded by overal_error
# #                     \d+  # A number that starts with any number
# #                     .    # A decimal point
# #                     \d+  # Any decimal part
# #                     e    # Exponent symbol
# #                     \+   # A plus sign
# #                     \d+  # Any exponent""",re.X)
