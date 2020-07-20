--
-- "declare" these two functions here, so the ide doesn't scream that they're unused
function Random() end
function MutexedWriter() end

--
-- defining a function for cpp to call
function Writings(n)
    for i = 1, 5 do
        Str = "\n[lua "
        Str = Str .. tostring(n)
        Str = Str .. " loop "
        Str = Str .. tostring(i)
        Str = Str .. " says "
        Str = Str .. tostring(Random()) -- calling a function passed to lua from cpp
        Str = Str .. "]"
        MutexedWriter(Str) -- calling a function passed to lua from cpp
    end
end

