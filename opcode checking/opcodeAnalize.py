import json

convert = {
    "AF": "AF.AF",
    "BC": "BC.BC",
    "DE": "DE.DE",
    "HL": "HL.HL",
    "A": "AF.A",
    "B": "BC.B",
    "D": "DE.D",
    "H": "HL.H",
    "F": "AF.F",
    "C": "BC.C",
    "E": "DE.E",
    "L": "HL.L",
    "SP": "SP",
    "PC": "PC",
    "n8": "fetch()",
    "n16": "n16",
    "e8": "fetch()",
    "NZ": "NZ",
    "a8": "fetch()",
    "a16": "a16",
    "Z": "Z",
    "NC": "NC",
}
def convertion(operand):
    if "$" in operand:
        return str(int(operand[1:]))
    else:
        return convert[operand]
def comment(operand):
    if operand == "n8":
        return "Immidiate"
with open("Opcodes.json", "r") as file:
    JSON = json.load(file)["unprefixed"]
    JSON = dict(sorted(JSON.items(), key=lambda item: item[1]["mnemonic"]))
    for e in JSON:
        print(f"""case {e}:
    {JSON[e]["mnemonic"]}({",".join([convertion(x["name"]) for x in JSON[e]["operands"]])}); //""")
