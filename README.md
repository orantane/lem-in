# lem-in
Hive Helsinki school project called "lem-in".

# Usage
./generator --[map_option] | ./lem-in -[flags] \
-- OR -- \
./lem-in [flags] < [a map from a file]

Map options are: flow-one, flow-ten, flow-thousand, big, big-superposition. \
Flag options and their descriptions can be found by running ./lem-in -h.

# The task
Our task was to create a program written in C, that finds the optimal solution to move ants in the most efficient way
through a maze of rooms that are connected to eachother via links. To achieve this we studied a number
of pathfinding algorithms and implemented our own version. We already optimize the program in multitude of ways,
for example we use a hash table to store the room names to speed up the room building process. To further optimize
the program, we could use another hash table for the linking of the rooms.

# The result
We ended up with a program that is fast and accurate. We also included a file that contains resources
for testing the program (maps, generator, testing script etc). The generator was provided to us in the subject.
We included a few flags as a bonus to make the output a bit more understandable in bigger maps.

# The subject and rules
A few lines from the subject that describes the project and its goals:

- We make an ant farm, with tunnels and rooms. We place the ants on one side
  and we look at how they find the exit.

- We join the rooms to one another with as many links as we need. A link joins
  two rooms to each other.

- A room can be linked to an infinite number of rooms and by as many links 
  as deemed necessary.
  
- The program will receive the data describing the ant farm from the standard
  output in the following format:
    * number_of_ants
    * the_rooms
    * the_links

- There are two parts:
  * The rooms, which are defined by: name coord_x coord_y
  * The links, which are defined by: name1-name2
  * All of it is broken by comments, which start with #

- Lines that start with ## are commands modifying the properties of the line
  that comes right after. For example, ##start signals the ant farm’s entrance
  and ##end its exit.

An example: \
#number_of_ants \
5 \
#the_rooms \
##start \
1 2 3 \
2 3 4 \
##end \
3 4 5 \
#the_links \
1-2 \
2-3

The goal of this project is to find the quickest way to get n ants across the farm.
- Quickest way means the solution with the least number of lines, respecting the
  output format requested below.
- Obviously, there are some basic constraints. To be the first to arrive, ants will need
  to take the shortest path (and that isn’t necessarily the simplest). They will also
  need to avoid traffic jams as well as walking all over their fellow ants.
- At the beginning of the game, all the ants are in the room ##start. The goal is
  to bring them to the room ##end with as few turns as possible. Each room can
  only contain one ant at a time. (except at ##start and ##end which can contain
  as many ants as necessary.)
- We consider that all the ants are in the room ##start at the beginning of the game.
- At each turn you will only display the ants that moved.
- At each turn you can move each ant only once and through a tube (the room at
  the receiving end must be empty).
- You must to display your results on the standard output in the following format:
    * number_of_ants
    * the_rooms
    * the_links
    * Lx-y Lz-w Lr-o ... \
    (x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y,
     w, o represents the rooms’ names.)
- Of course, your algorithm must render within a reasonable time, even in a case with
  4000 rooms. 2 or 3 seconds is great, 9 seconds is mediocre, 15 seconds is too much.

- Within the mandatory part you are allowed to use the following functions:
  * malloc
  * free
  * read
  * write
  * strerror
  * perror
  * exit
