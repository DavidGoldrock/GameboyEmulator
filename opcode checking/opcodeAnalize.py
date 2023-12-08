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
    "n8": "this->cpu->n8",
    "n16": "this->cpu->n16",
    "e8": "this->cpu->e8",
    "NZ": "this->cpu->NZ",
    "a8": "this->cpu->a8",
    "a16": "this->cpu->a16",
    "Z": "this->cpu->Z",
    "NC": "this->cpu->NC",
}
instructionSet = set(())
caseList = []

def comment(operand):
    if operand == "n8":
        return "Immidiate"


def setFlags(flags):
    returnVal = ""
    returnVal2 = ""
    for element in flags:
        if flags[element] == element:
            returnVal2 += f"        // calculate {element}  this->cpu->set{element}Flag();\n"
        elif flags[element] != '-':
            returnVal += f"        this->cpu->set{element}Flag({'true' if flags[element] == '1' else 'false'});\\\n"
    return ((returnVal[:-2] + "\n") + (returnVal2 if returnVal2 != "" else ""))[:-1]


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

class opcode:
    def __init__(self,value, mnemonic, variables, flags, cycles, conditions):
        self.value = value
        self.mnemonic =mnemonic
        self.variables =variables
        self.flags =flags
        self.cycles =cycles
        self.conditions =conditions

    def __hash__(self):
        return hash((self.value, self.mnemonic, ",".join(self.variables), ",".join(self.flags), self.cycles,",".join(self.conditions)))

    def __eq__(self, other):
        if not isinstance(other, type(self)): return NotImplemented
        return self.value == other.value and self.mnemonic == other.mnemonic and self.variables == other.variables and self.flags == other.flags and self.cycles == other.cycles and self.conditions == other.conditions

def generateOpcodeLists(JSON):
    JSON = dict(sorted(JSON.items(), key=lambda item: item[1]["mnemonic"]))
    for e in JSON:
        noCond = [x["name"] for x in JSON[e]['operands'] if x["name"] not in ["Z", "NZ", "NC"]]
        cond = [x["name"] for x in JSON[e]['operands'] if x["name"] in ["Z", "NZ", "NC"]]
        op = opcode(e,generateMnemonic(JSON[e]["mnemonic"]), noCond,JSON[e]['flags'], JSON[e]['cycles'][0],cond)
        instructionSet.add(op)
        caseList.append(op)

def generateCases(caseList):
    special = ["n8",
           "n16",
           "e8",
           "a8",
           "a16"]
    for op in caseList:
        variableAssigning = ""
        actualVariables = []
        for var in op.variables:
            if var in special:
                if "8" in var:
                    variableAssigning += f"{var} = fetch();\n"
                    actualVariables.append(var)

                else:
                    variableAssigning += f"{var} = fetch16();\n"
                    actualVariables.append(var)

            elif var.isnumeric():
                variableAssigning += f"this->cpu->im = {str(int(var))};\n"
            elif var[1:].isnumeric():
                variableAssigning += f"this->cpu->im = {str(int(var[1:]))};\n"
            else:
                actualVariables.append(var)
        print(f"""  case {op.value}:
                {variableAssigning}
                {op.mnemonic}{'_' + str(op.cycles) + '_' + str(len(op.variables)) + ('_' if len(op.conditions) > 0 else '') + '_'.join(op.conditions)}({",".join([convert[x] for x in actualVariables])});
                break;""")

def generateCommands(instructionSet):
    l = []
    for element in instructionSet:
        operandlist = []
        for i in range(len(element.variables)):
            operandlist.append("operand" + str((i + 1)))
        string1 = f"#define {element.mnemonic}{'_' + str(element.cycles) + '_' + str(len(element.variables)) + ('_' if len(element.conditions) > 0 else '') + '_'.join(element.conditions)}({','.join(operandlist)})\\\n"
        if len(element.conditions) > 0:
            string1 += "if("
            if "Z" in element.conditions:
                string1 += " this->cpu->getZFlag()"
            if "NZ" in element.conditions:
                string1 += " !this->cpu->getZFlag()"
            if "NC" in element.conditions:
                string1 += " !this->cpu->getCFlag()"
            string1 += ") {"
        string1 += f"std::cout << \"{element.mnemonic}{'_' + str(element.cycles) + ('_' if len(element.conditions) > 0 else '') + '_'.join(element.conditions)}\" << std::endl;\\\n"
        string1 += f"{delayCycles(element.cycles)}\\\n"
        string1 += f"{setFlags(element.flags)}\n"
        if len(element.conditions) > 0:
            string1 = string1[:-1]
            string1 += "}"
        l.append(string1)
    l = sorted(l)
    for command in l:
        print(command)


with open("Opcodes.json", "r") as file:
    JSONFILE = json.load(file)

    print("if(!this->cpu->isPrefixed) {")
    print("    switch(opcode) {")
    generateOpcodeLists(JSONFILE["unprefixed"])
    generateCases(caseList)
    print("    }\n}")
    print("else {")
    print("    switch(opcode) {")

    instructionSet = set(())
    caseList = []
    generateOpcodeLists(JSONFILE["cbprefixed"])
    generateCases(caseList)
    print("    }\n}")


    # instructionSet = set(())
    # caseList = []
    # generateOpcodeLists(JSONFILE["unprefixed"])
    # generateOpcodeLists(JSONFILE["cbprefixed"])
    # generateCommands(instructionSet)
