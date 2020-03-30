from random import randint, random
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from copy import deepcopy
from math import sqrt

MAP_HEIGHT = 500
MAP_WIDTH = MAP_HEIGHT
CENTER = (MAP_WIDTH/2, MAP_HEIGHT/2)
NB_CYLES = 1000
data = []
SUSCEPTIBLE, INFECTIOUS, RECOVERED, DEAD = range(4)
INFECTION_RADIUS = 10
PROB_INFECION = 0.2
DEATH_RATE = 0.001
INFECTION_DURATION = 100
dt = 0.01
fig, ax = plt.subplots(figsize=(12,8))
BIG_G = 1e4
gravity_points = []


class Point(object):
    def __init__(self, position, speed=np.array([0,0]), mobile=True, mass=1):
        self.mobile = mobile
        self.position = position
        self.speed = speed
        self.mass = mass

    def get_distance_to(self, other):
        x1, y1 = self.position
        x2, y2 = other.position
        return sqrt((x2 - x1)**2 + (y2 - y1)**2)

    def is_safe_to_move(self, position):
        x = position[0]
        y = position[1]
        return x >= 0 and x < MAP_HEIGHT and y >= 0 and y < MAP_WIDTH

    def get_closest_edge(self, position):
        x, y = px, py = position
        if px < 0:
            x = 0
        elif px >= MAP_WIDTH:
            x = MAP_WIDTH - 1
        if py < 0:
            y = 0
        elif py >= MAP_HEIGHT:
            y = MAP_HEIGHT - 1
        return np.array([x, y])

    def move(self, position=-1, direction=-1):
        if self.mobile == True:   
            new_position = self.position
            if not position == -1:       #some position has been given
                new_position = position
            elif not direction == -1:            #some direction has been given
                new_position = new_position + direction
            else:
               # self.update_speed()
                new_position = self.position + self.speed * dt
                
            if self.is_safe_to_move(new_position):
                self.position = new_position
            else:
                self.position = self.get_closest_edge(new_position)

    def get_neighbours(self, distance):
        neighbours = []
        for person in population.population:
            if self.get_distance_to(person) <= distance:
                neighbours.append(person)
        return neighbours

class GravityPoint(Point):
    def __init__(self, position, mass, speed=np.array([0,0]), mobile=True):
        Point.__init__(self,position,speed, mobile)
        self.mass = mass
    
    def update_speed(self):
        if self.position[0] == 0:
            self.speed = np.array([10,0])
        elif self.position[0] == MAP_WIDTH-1:
            self.speed = np.array([-10,0])

class Person(Point):

    def __init__(self, position, health_state, speed=np.array([0,0]), mobile=True, mass=1):
        Point.__init__(self, position, speed, mobile, mass)
        self.health_state = health_state
        self.infection_duration = 0
        self.repulsion_radius = 100

    def get_force(self, point):
        dist = (self.get_distance_to(point))
        return BIG_G * (point.position - self.position) * point.mass / (dist+1)**3

    def update_speed(self,point):
        force = -self.get_force(point)

       # random_force = self.get_force(Point(random_position(),mass=10))
      #  force = force + random_force
        vx, vy = self.speed + force * dt
        limit = 200
        if vx < -limit:
            vx = -limit
        elif vx > limit:
            vx = limit
        if vy < -limit:
            vy = -limit
        elif vy > limit:
            vy = limit
        self.speed = np.array([vx, vy])
    

    def will_die(self):
        p = random()
        return p <= DEATH_RATE

    def get_random_direction(self):
        dx = randint(-1,1)
        dy = randint(-1,1)
        return dx, dy
  
class Population(object):
   
    def __init__(self, size_population):
        self.population = []
        patient_zero = Person(np.array(CENTER), INFECTIOUS, mass = 1)
        self.population.append(patient_zero)
        for i_person in range(size_population-1):
            self.population.append(Person(random_position(), SUSCEPTIBLE))
        
    def get_positions(self, health_state):
        P = [self.population[i].position for i in range(len(self.population)) if self.population[i].health_state == health_state]
        return P


    def update_population(self):
        for person1 in self.population:
            if person1.health_state == DEAD:
                continue
           # if person1.health_state == INFECTIOUS:
        #        if person1.will_die():
         #           person1.health_state = DEAD
        #            continue
        #        person1.infection_duration += 1
         #       if person1.infection_duration > INFECTION_DURATION:
         #           person1.health_state = RECOVERED
         #       else:
            for person2 in self.population:
                person1.update_speed(person2)
                x, y = person1.position
                walls_pos = [[x,-1],[x,MAP_HEIGHT],[-1,y],[MAP_WIDTH,y]]
                walls = []
                for i in range(4):
                    walls.append(Point(np.array(walls_pos[i]),mass=4))
                for wall in walls:
                    person1.update_speed(wall)

                if person2.health_state == SUSCEPTIBLE and person1.get_distance_to(person2) <= INFECTION_RADIUS:
                    if random() <= PROB_INFECION:
                        person2.health_state = INFECTIOUS
            person1.move()


def random_position():
    return np.array([randint(0,MAP_WIDTH), randint(0,MAP_HEIGHT)])

def random_direction():
    return np.array([randint(-30,30), randint(-30,30)])

def animate(i):
    colors = ["black", "red", "green"]
    scatters = []
    for health_state in range(3):
        positions = data[i].get_positions(health_state)
        x = [positions[j][0] for j in range(len(positions))]
        y = [positions[j][1] for j in range(len(positions))]

        scat = ax.scatter(x, y, c=colors[health_state])
        scatters.append(scat)

    return scatters


population = Population(7)

def main():
    ax.set(xlim=(0, MAP_WIDTH), ylim=(0, MAP_HEIGHT))

    data.append(deepcopy(population))
    
   
    

    for i in range(NB_CYLES):
        population.update_population()
        data.append(deepcopy(population))

    ani = animation.FuncAnimation(fig, animate,NB_CYLES, None, interval=dt*1000, blit=True, repeat=True)
    #Writer = animation.writers['ffmpeg']
    #writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)
    #ani.save("Video.mp4", writer="imagemagick")
    plt.show()



main()
