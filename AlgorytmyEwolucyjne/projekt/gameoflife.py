# %%
"""
Projekt na programowanie ewolucyjne

Celem projektu jest znalezienie układu żywych komórek w Conway's game of life które maksymalizują liczbę żywych komórek po określonej liczbie tur (np. 10, 20,...).
"""

# %%
import numpy as np
import matplotlib.pyplot as plt

rng = np.random.default_rng()

# %%
# osobnik to np.array 1-d z zerami i jedynkami

def printindividual( v, height, width ):
    print( v.reshape( (height, width) ) )

def imageprintindividual( v, height, width ):
    t = v.reshape( (height, width) )
    fig = plt.figure()
    ax = plt.axes()
    im = ax.imshow(t, cmap='binary')

def simulategameoflife( v, height, width, turns):
    #print("simulation at beginning:")
    #printindividual( v, height, width )

    game = v.reshape( (height, width ) )
    lastnonzero = 0

    around = [ (a, b) for a in [-1, 0, 1] for b in [-1, 0, 1] if (a, b) != (0, 0) ]
    for iturn in range( turns ):
        newgame = np.zeros( game.shape, dtype=int)
        for i in range( height ):
            for j in range( width ):
                pos = (i, j)
                neighboursidx = [ (x + i, y + j) for (x, y) in around if (0 <= x + i and x + i < height) and (0 <= y + j and (y + j < width) )]
                #print( neighboursidx )
                #print( np.array( neighboursidx ) )
                #print(  game[ np.array(neighboursidx)[:, 0], np.array(neighboursidx)[:, 1] ]  )
                aliveneighbours = np.count_nonzero( game[ np.array(neighboursidx)[:, 0], np.array(neighboursidx)[:, 1] ] )
                #if aliveneighbours == 2:
                #    newgame[ i, j ] = game[ i, j ]
                if aliveneighbours == 2 and game[ i, j ] == 1:
                    newgame[ i, j ] = 1
                else:
                    if aliveneighbours == 3:
                        newgame[ i, j ] = 1
                    else:
                        newgame[ i, j ] = 0
                #print(f"i:{i}, j:{j}, game[]:{game[i, j]}, newgame:{newgame[i, j]}, aliveneighbours:{aliveneighbours}")

        #print( newgame )
        #imageprintindividual( game, height, width )

        game = newgame
        if np.count_nonzero(game) > 0:
            lastnonzero = iturn

    return game, lastnonzero

#simulategameoflife( rng.integers(2, size=100), 10, 10, 10 )


# %%
def random_individual( d ):
    return rng.integers(2, size=d)

def random_population( n, d ):
    POP = np.zeros( (n, d), dtype=np.int32)
    for i in range(n):
        POP[i] = random_individual( d )
    return POP

def population_evaluation(P, F):
    res = np.zeros(P.shape[0])
    for i in range(P.shape[0]):
        res[i] = F(P[i])
    return res

# %%
def gameoflifeobjfunc( v, height, width, turns ):
    game, last = simulategameoflife( v, height, width, turns )
    return np.count_nonzero(game) * (turns) + last

def simplecrossover( v1, v2 ):
    n = v1.shape[0]
    cutoff = rng.choice( n, 1 )[0]
    #print(cutoff)
    for i in range( cutoff, n ):
        tmp = v2[i]
        v2[i] = v1[i]
        v1[i] = tmp
    return v1, v2

#operator mutacji, który zamienia między dwoma osobnikami losowo wybrany kwadrat
def squarecrossover( v1, v2, height, width ):
    x1 = rng.integers( 0, height - 1 )
    y1 = rng.integers( 0, width - 1 )
    x2 = rng.integers( x1, height )
    y2 = rng.integers( y1, width )
    for i in range( x1, x2 + 1 ):
        for j in range( y1, y2 + 1 ):
            idx = i * width + j
            tmp = v2[idx]
            v2[idx] = v1[idx]
            v1[idx] = tmp
    return v1, v2


def simplemutation( v, singleprobability = 0.05 ):
    for i in range( v.shape[0] ):
        if rng.random() < singleprobability:
            if v[i] == 0:
                v[i] = 1
            else:
                v[i] = 0
    return v


# %%
def SGA(chromosome_length, population_size, objfunction, crossover_probability = 0.95, mutation_probability = 0.25, number_of_iterations=250):
    number_of_offspring = population_size

    best_objective_value = 0
    best_chromosome = np.zeros((1, chromosome_length))

    # generating an initial population
    current_population = random_population( population_size, chromosome_length )

    # evaluating the objective function on the current population
    objective_values = population_evaluation( current_population, objfunction )

    plotdata = np.zeros((4,number_of_iterations))

    for t in range(number_of_iterations):

        # selecting the parent indices by the roulette wheel method
        fitness_values = objective_values.max() - objective_values
        if fitness_values.sum() > 0:
            fitness_values = fitness_values / fitness_values.sum()
        else:
            fitness_values = np.ones(population_size) / population_size
        parent_indices = np.random.choice(population_size, number_of_offspring, True, fitness_values).astype(np.int32)

        # creating the children population
        children_population = np.zeros((number_of_offspring, chromosome_length), dtype=np.int32)
        for i in range(int(number_of_offspring/2)):
            if np.random.random() < crossover_probability:
                children_population[2*i, :], children_population[2*i+1, :] = simplecrossover(current_population[parent_indices[2*i], :].copy(), current_population[parent_indices[2*i+1], :].copy())
            else:
                children_population[2*i, :], children_population[2*i+1, :] = current_population[parent_indices[2*i], :].copy(), current_population[parent_indices[2*i+1]].copy()
        if np.mod(number_of_offspring, 2) == 1:
            children_population[-1, :] = current_population[parent_indices[-1], :]

        # mutating the children population
        for i in range(number_of_offspring):
            if np.random.random() < mutation_probability:
                children_population[i, :] = simplemutation(children_population[i, :])

        # evaluating the objective function on the children population
        children_objective_values = population_evaluation( children_population, objfunction )

        # replacing the current population by (Mu + Lambda) Replacement
        objective_values = np.hstack([objective_values, children_objective_values])
        current_population = np.vstack([current_population, children_population])

        I = np.argsort(objective_values)[::-1]
        current_population = current_population[I[:population_size], :]
        objective_values = objective_values[I[:population_size]]

        # recording some statistics
        if best_objective_value < objective_values[0]:
            best_objective_value = objective_values[0]
            best_chromosome = current_population[0, :]

        plotdata[0, t] = objective_values.min()
        plotdata[1, t] = objective_values.mean()
        plotdata[2, t] = objective_values.max()
        plotdata[3, t] = objective_values.std()

        if t % 100 == 0:
            print('%3d %12.8f %12.8f %12.8f %12.8f' % (t, objective_values.min(), objective_values.mean(), objective_values.max(), objective_values.std()))
    return plotdata, best_chromosome

# %%
def objfuncfor10x10t10(v):
    return gameoflifeobjfunc( v, 10, 10, 10 )

def objfuncfor10x10t20(v):
    return gameoflifeobjfunc( v, 10, 10, 20 )

def objfuncfor10x10t50(v):
    return gameoflifeobjfunc( v, 10, 10, 50 )

def objfuncfor10x10t100(v):
    return gameoflifeobjfunc( v, 10, 10, 100 )


def objfuncfor20x20t10(v):
    return gameoflifeobjfunc( v, 20, 20, 10 )

def objfuncfor20x20t20(v):
    return gameoflifeobjfunc( v, 20, 20, 20 )

def objfuncfor20x20t50(v):
    return gameoflifeobjfunc( v, 20, 20, 50 )

def objfuncfor20x20t100(v):
    return gameoflifeobjfunc( v, 20, 20, 100 )
    

def makeplots(plotdata, solution, height, width, turns):
    plt.plot(plotdata[0], label='min')
    plt.plot(plotdata[1], label='mean')
    plt.plot(plotdata[2], label='max')
    plt.legend()
    plt.show()

    print("najlepsza plansza na starcie")
    imageprintindividual(solution, height, width)
    print("plansza po ", turns, " turach")
    imageprintindividual(simulategameoflife(solution, height, width, turns)[0], height, width)

# %%
"""
Wyniki w poniższych wykresach są liczone według wzoru tury * (liczba żywych pozostałych komórek) + tury ktore przezyla jakakolwiek komórka, aby rozróżnić plansze z której żadna komórka nie przeżywa 10 tur (lepsze są takie które przeżyją dłużej)
"""

# %%
print("10x10:")
print("10 tur:")
plotdata, solution = SGA(100, 100, objfuncfor10x10t10, number_of_iterations=500)
makeplots(plotdata, solution, 10, 10, 10)

print("20 tur:")
plotdata, solution = SGA(100, 100, objfuncfor10x10t20, number_of_iterations=500)
makeplots(plotdata, solution, 10, 10, 20)

print("50 tur:")
plotdata, solution = SGA(100, 100, objfuncfor10x10t50, number_of_iterations=500)
makeplots(plotdata, solution, 10, 10, 50)

print("100 tur:")
plotdata, solution = SGA(100, 100, objfuncfor10x10t100, number_of_iterations=500)
makeplots(plotdata, solution, 10, 10, 100)




# %%
print("20x20:")
print("10 tur:")
plotdata, solution = SGA(400, 400, objfuncfor20x20t10, number_of_iterations=500)
makeplots(plotdata, solution, 20, 20, 10)

print("20 tur:")
plotdata, solution = SGA(400, 400, objfuncfor20x20t20, number_of_iterations=500)
makeplots(plotdata, solution, 20, 20, 20)

print("50 tur:")
plotdata, solution = SGA(400, 400, objfuncfor20x20t50, number_of_iterations=500)
makeplots(plotdata, solution, 20, 20, 50)

print("100 tur:")
plotdata, solution = SGA(400, 400, objfuncfor20x20t100, number_of_iterations=500)
makeplots(plotdata, solution, 20, 20, 100)


# %%
def SGAsquarecross(chromosome_length, population_size, objfunction, gameheight, gamewidth, crossover_probability = 0.95, mutation_probability = 0.25, number_of_iterations=250):
    number_of_offspring = population_size

    best_objective_value = 0
    best_chromosome = np.zeros((1, chromosome_length))

    # generating an initial population
    current_population = random_population( population_size, chromosome_length )

    # evaluating the objective function on the current population
    objective_values = population_evaluation( current_population, objfunction )

    plotdata = np.zeros((4,number_of_iterations))

    for t in range(number_of_iterations):

        # selecting the parent indices by the roulette wheel method
        fitness_values = objective_values.max() - objective_values
        if fitness_values.sum() > 0:
            fitness_values = fitness_values / fitness_values.sum()
        else:
            fitness_values = np.ones(population_size) / population_size
        parent_indices = np.random.choice(population_size, number_of_offspring, True, fitness_values).astype(np.int32)

        # creating the children population
        children_population = np.zeros((number_of_offspring, chromosome_length), dtype=np.int32)
        for i in range(int(number_of_offspring/2)):
            if np.random.random() < crossover_probability:
                children_population[2*i, :], children_population[2*i+1, :] = squarecrossover(current_population[parent_indices[2*i], :].copy(), current_population[parent_indices[2*i+1], :].copy(), gameheight, gamewidth)
            else:
                children_population[2*i, :], children_population[2*i+1, :] = current_population[parent_indices[2*i], :].copy(), current_population[parent_indices[2*i+1]].copy()
        if np.mod(number_of_offspring, 2) == 1:
            children_population[-1, :] = current_population[parent_indices[-1], :]

        # mutating the children population
        for i in range(number_of_offspring):
            if np.random.random() < mutation_probability:
                children_population[i, :] = simplemutation(children_population[i, :])

        # evaluating the objective function on the children population
        children_objective_values = population_evaluation( children_population, objfunction )

        # replacing the current population by (Mu + Lambda) Replacement
        objective_values = np.hstack([objective_values, children_objective_values])
        current_population = np.vstack([current_population, children_population])

        I = np.argsort(objective_values)[::-1]
        current_population = current_population[I[:population_size], :]
        objective_values = objective_values[I[:population_size]]

        # recording some statistics
        if best_objective_value < objective_values[0]:
            best_objective_value = objective_values[0]
            best_chromosome = current_population[0, :]

        plotdata[0, t] = objective_values.min()
        plotdata[1, t] = objective_values.mean()
        plotdata[2, t] = objective_values.max()
        plotdata[3, t] = objective_values.std()

        if t % 100 == 0:
            print('%3d %12.8f %12.8f %12.8f %12.8f' % (t, objective_values.min(), objective_values.mean(), objective_values.max(), objective_values.std()))
    return plotdata, best_chromosome

# %%
print("10x10 with squarecrossover:")
print("10 tur:")
plotdata, solution = SGAsquarecross(100, 100, objfuncfor10x10t10, 10, 10, number_of_iterations=500)
makeplots(plotdata, solution, 10, 10, 10)

print("20 tur:")
plotdata, solution = SGAsquarecross(100, 100, objfuncfor10x10t20, 10, 10, number_of_iterations=500)
makeplots(plotdata, solution, 10, 10, 20)

print("50 tur:")
plotdata, solution = SGAsquarecross(100, 100, objfuncfor10x10t50, 10, 10, number_of_iterations=500)
makeplots(plotdata, solution, 10, 10, 50)

print("100 tur:")
plotdata, solution = SGAsquarecross(100, 100, objfuncfor10x10t100, 10, 10, number_of_iterations=500)
makeplots(plotdata, solution, 10, 10, 100)


# %%
print("20x20 with squarecrossover:")
print("10 tur:")
plotdata, solution = SGA(400, 400, objfuncfor20x20t10, 10, 10, number_of_iterations=500)
makeplots(plotdata, solution, 20, 20, 10)

print("20 tur:")
plotdata, solution = SGA(400, 400, objfuncfor20x20t20, 10, 10, number_of_iterations=500)
makeplots(plotdata, solution, 20, 20, 20)

print("50 tur:")
plotdata, solution = SGA(400, 400, objfuncfor20x20t50, 10, 10, number_of_iterations=500)
makeplots(plotdata, solution, 20, 20, 50)

print("100 tur:")
plotdata, solution = SGA(400, 400, objfuncfor20x20t100, 10, 10, number_of_iterations=500)
makeplots(plotdata, solution, 20, 20, 100)

# %%
"""
Porównanie z maksymalnym wynikiem policzonym dla wszystkich możliwych układów komórek początkowych
"""

# %%
def bestsolutionslow(height, width, turns = 10):
    n = height * width

    bestres = 0
    solution = np.zeros( n )
    solutionsimulated = np.zeros( n )

    #all subsets of alive cells
    for mask in range( 1, 1 << n ):
        s = [ j for j in range( n ) if (mask & (1 << j)) != 0 ] # subset

        start = np.zeros(n)
        #print(s)
        start[ np.array(s) ] = 1
        #print(mask)

        gameend, _ = simulategameoflife( start, height, width, turns )
        res = np.count_nonzero(gameend)
        if res > bestres:
            bestres = res
            solution = np.array(start)
            solutionsimulated = gameend

    
    return solution, solutionsimulated, bestres
                

# %%
# 4x4
brutesolution, brutesim, bruteres = bestsolutionslow(4, 4, 10)


# %%
print("dla 4x4 najlepsze rozwiazanie po 10 turach ma", bruteres, "zywych komorek, wyglada ono tak:")
imageprintindividual(brutesolution, 4, 4)
print("po 10 turach:")
imageprintindividual(brutesim, 4, 4)

# %%
def objfuncfor4x4(v):
    return gameoflifeobjfunc( v, 4, 4, 10 )

plotdata, solution = SGA(16, 100, objfuncfor4x4, number_of_iterations=400)

makeplots(plotdata, solution, 4, 4, 10)


# %%
def random_neighbor(v, radius):
    res = np.array(v.shape)
    idx = rng.choice( v.shape[0] - 1, size=radius, replace=False )
    res = v.copy()
    for i in idx:
        if res[idx] == 1:
            res[idx] = 0
        else:
            res[idx] = 1
    return res

def simulated_annealing(d, obj_func, T = 5000, radius = 1, alpha = 1.0):
    p = random_individual(d)
    p_cost = obj_func(p)
    costs = np.zeros(T)
    for t in range(T):
        q = random_neighbor(p, radius)
        q_cost = obj_func(q)
        if(q_cost > p_cost):
            p, p_cost = q, q_cost
        elif(np.random.rand() < np.exp(- alpha * (p_cost - q_cost) * t/T)):
            p, p_cost = q, q_cost
        costs[t] = p_cost

        if t % 100 == 0:
            print(t)

    return costs, p




# %%
def printannealing(annealing_costs, annealing_solution):
    plt.figure(figsize=(12,4))
    plt.plot(annealing_costs)
    plt.show()

    imageprintindividual(annealing_solution, 10, 10)
    imageprintindividual(simulategameoflife(annealing_solution, 10, 10, 10)[0], 10, 10)

# %%
print("simulated annealing 10x10:")
print("10 tur")
annealing_costs, annealing_solution = simulated_annealing( 100, objfuncfor10x10t10, T = 4000 )
printannealing(annealing_costs, annealing_solution)

print("20 tur")
annealing_costs, annealing_solution = simulated_annealing( 100, objfuncfor10x10t20, T = 4000 )
printannealing(annealing_costs, annealing_solution)

print("50 tur")
annealing_costs, annealing_solution = simulated_annealing( 100, objfuncfor10x10t50, T = 4000 )
printannealing(annealing_costs, annealing_solution)

print("100 tur")
annealing_costs, annealing_solution = simulated_annealing( 100, objfuncfor10x10t100, T = 4000 )
printannealing(annealing_costs, annealing_solution)

# %%
print("simulated annealing 20x20:")
print("10 tur")
annealing_costs, annealing_solution = simulated_annealing( 400, objfuncfor20x20t10, T = 4000 )
printannealing(annealing_costs, annealing_solution)

print("20 tur")
annealing_costs, annealing_solution = simulated_annealing( 400, objfuncfor20x20t20, T = 4000 )
printannealing(annealing_costs, annealing_solution)

print("50 tur")
annealing_costs, annealing_solution = simulated_annealing( 400, objfuncfor20x20t50, T = 4000 )
printannealing(annealing_costs, annealing_solution)

print("100 tur")
annealing_costs, annealing_solution = simulated_annealing( 400, objfuncfor20x20t100, T = 4000 )
printannealing(annealing_costs, annealing_solution)