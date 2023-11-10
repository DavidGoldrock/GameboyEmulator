import json

convert = {
    "AF": "this->cpu->AF.AF",
    "BC": "this->cpu->BC.BC",
    "DE": "this->cpu->DE.DE",
    "HL": "this->cpu->HL.HL",
    "A": "this->cpu->AF.A",
    "B": "this->cpu->BC.B",
    "D": "this->cpu->DE.D",
    "H": "this->cpu->HL.H",
    "F": "this->cpu->AF.F",
    "C": "this->cpu->BC.C",
    "E": "this->cpu->DE.E",
    "L": "this->cpu->HL.L",
    "SP": "this->cpu->SP",
    "PC": "this->cpu->PC",
    "n8": "fetch()",
    "n16": "n16",
    "e8": "fetch()",
    "NZ": "NZ",
    "a8": "fetch()",
    "a16": "a16",
    "Z": "Z",
    "NC": "NC",
}
instructionSet = set(())


def convertion(operand):
    if "$" in operand:
        return str(int(operand[1:]))
    elif operand.isnumeric():
        return operand
    else:
        return convert[operand]


def comment(operand):
    if operand == "n8":
        return "Immidiate"


def setFlags(flags):
    returnVal = ""
    for element in flags:
        if flags[element] == element:
            returnVal += f"        // calculate {element}  this->cpu->set{element}Flag();\n"
        else:
            returnVal += f"        this->cpu->set{element}Flag({'true' if flags[element] == '1' else 'false'});\n"
    return returnVal[:-1]


def delayCycles(cycles):
    if (str(cycles)).isnumeric():
        return f"        this->delayCycles({cycles});"
    if len(cycles) == 0:
        return ""
    if len(cycles) == 1:
        return f"        this->delayCycles({cycles[0]});"
    return f"        this->delayCycles({cycles});{'// MULTIPLE TIMING OPTIONS:' + ','.join(cycles[1:])}"

def generateMnemonic(mnemonic):
    if "ILLEGAL" in mnemonic:
        return "ILLEGAL"
    return mnemonic

def generateCases(JSON):
    JSON = dict(sorted(JSON.items(), key=lambda item: item[1]["mnemonic"]))
    for e in JSON:
        instructionSet.add((generateMnemonic(JSON[e]["mnemonic"]), len(JSON[e]['operands'])))
        print(f"""  case {e}:
        {generateMnemonic(JSON[e]["mnemonic"])}({",".join([convertion(x["name"]) for x in JSON[e]["operands"]])});
{setFlags(JSON[e]["flags"])}
{delayCycles(JSON[e]['cycles'][0])}
        break;""")

def generateCommands(instructionSet):
    l = []
    for element in instructionSet:
        operandlist = []
        for i in range(element[1]):
            operandlist.append("operand" + str((i + 1)))
        l.append(f"#define {element[0]}({','.join(operandlist)})")
    l = sorted(l)
    for command in l:
        print(command)
with open("Opcodes.json", "r") as file:
    JSONFILE = json.load(file)
    print("if(this->cpu->isPrefixed) {")
    print("    switch(opcode) {")
    generateCases(JSONFILE["unprefixed"])
    print("    }\n}")
    print("else {")
    print("    switch(opcode) {")
    generateCases(JSONFILE["cbprefixed"])
    print("    }\n}")
    generateCommands(instructionSet)
