# Based on
#   S-M. Hu: Conversion of a triangular Bezier patch into three rectangular Bezier patches (1996)

# (here only for the quadratic case)

"""
    split(T, filename)

Writes a one-third split into `filename`.
`T` is assumed to be `[T00,T01,T02,T10,T11,T20]`.
     -> indices:        1   2   3   4   5   6
"""
function split(T, filename)
    open(filename, "w") do f
        pvec(x) = println(f, "$(x[1]) $(x[2]) $(x[3])")
        println(f, "2 2")
        pvec(T[1])
        pvec((T[1]+T[2])/2)
        pvec((T[1]+2*T[2]+T[3])/4)
        pvec((T[1]+T[4])/2)
        pvec((7*T[1]+7*T[2]+7*T[4]+3*T[5])/24)
        pvec((T[1]+2*T[2]+T[3]+T[4]+T[5])/6)
        pvec((T[1]+2*T[4]+T[6])/4)
        pvec((T[1]+T[2]+2*T[4]+T[5]+T[6])/6)
        pvec((T[1]+2*T[2]+T[3]+2*T[4]+2*T[5]+T[6])/9)
    end
end

rot(T) = [T[6],T[4],T[1],T[5],T[2],T[3]]

