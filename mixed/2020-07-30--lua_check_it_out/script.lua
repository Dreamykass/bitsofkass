
GlobalTable = {}

GlobalTable[000] = "foo"
GlobalTable[001] = "bar"
GlobalTable[002] = "fez"
GlobalTable[555] = "boo"

function TableFromFunction()
    table = {}

    table[000] = "foo"
    table[001] = "bar"
    table[002] = "fez"
    table[555] = "boo"

    return table
end