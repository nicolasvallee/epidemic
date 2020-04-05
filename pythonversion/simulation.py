from random import randint, random
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from copy import deepcopy
from math import sqrt,cos,sin
import my_module

MAP_HEIGHT = 500
MAP_WIDTH = MAP_HEIGHT
CENTER = (MAP_WIDTH/2, MAP_HEIGHT/2)
NB_CYLES = 500
data = []
SUSCEPTIBLE, INFECTIOUS, RECOVERED, DEAD = range(4)
INFECTION_RADIUS = 20
PROB_INFECION = 0.2
DEATH_RATE = 0.001
INFECTION_DURATION = 1000
dt = 1/60 #seconds
fig, ax = plt.subplots(figsize=(12,8))
BIG_G = 1e5
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
        x, y = position
        return x >= 0 and x < MAP_HEIGHT and y >= 0 and y < MAP_WIDTH

    ##Points must be inside when calling this function
    def get_closest_walls(self):
        walls = []
        x,y = self.position
        positions = np.array([[x,0],[x,MAP_HEIGHT-1],[0,y],[MAP_WIDTH-1,y]])
        for i in range(4):
            walls.append(Point(positions[i], mass=10))
        return walls

    def put_back_inside(self):                                             
        x, y = px, py = self.position
        if px < 0:
            x = 0
        elif px > MAP_WIDTH-1:
            x = MAP_WIDTH - 1
        if py < 0:
            y = 0
        elif py > MAP_HEIGHT-1:
            y = MAP_HEIGHT - 1

        self.position = np.array([x, y])

    def get_gravity_force(self, point):
        dist = self.get_distance_to(point)
        return BIG_G * (point.position - self.position) * self.mass * point.mass / (dist+1)**3

    def move(self, position=-1, direction=-1):
        if self.mobile == True:   
            new_position = self.position
            if not position == -1:          #some position has been given
                new_position = position
            elif not direction == -1:            #some direction has been given
                new_position = new_position + direction
            else:
                self.update_speed()
                new_position = self.position + self.speed * dt
            if self.is_safe_to_move(new_position):
                self.position = new_position
            else:
                self.put_back_inside()

    

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


    def update_speed(self):
        force = np.array([0,0])
        for person in population:
                force = force - self.get_gravity_force(person)
        walls = self.get_closest_walls()
        for wall in walls:
            force = force - self.get_gravity_force(wall)
        
        b = 4
        perpendicular_force = b * rotate_vector(self.speed, (-2*(random()<=0.5)+1) * np.pi/4)
        force = force + perpendicular_force
        #random_force = np.array([randint(-100,100) for i in range(2)])
        #force = force + random_force
        
        viscosity = 0.02
        force = force - viscosity * self.speed * np.linalg.norm(self.speed)
        vx, vy = self.speed + force / self.mass * dt

        self.speed = np.array([vx, vy])
    
    def contaminate_population(self):
        for person in population:
            if person.health_state == SUSCEPTIBLE and self.get_distance_to(person) <= INFECTION_RADIUS:
                if random() <= PROB_INFECION:
                    person.health_state = INFECTIOUS

    def will_die(self):
        p = random()
        return p <= DEATH_RATE

  

def rotate_vector(vector, angle):       #trigonometric direction
    rotation_matrix = np.array([[cos(angle), -sin(angle)],
                               [sin(angle), cos(angle)]])
    return rotation_matrix.dot(vector)

def generate_population(size):
    population = []
    patient_zero = Person(np.array(CENTER), INFECTIOUS, mass = 1, speed=np.array([0,0]))
    population.append(patient_zero)
    for i_person in range(size-1):
        population.append(Person(random_position(), SUSCEPTIBLE, speed=random_direction()))
    return population 



def update_population():
    for person in population:
        if person.health_state == DEAD:
            continue
        if person.health_state == INFECTIOUS:
            if person.will_die():
                person.health_state = DEAD
                continue
            
            person.infection_duration += 1
            if person.infection_duration > INFECTION_DURATION:
                person.health_state = RECOVERED
            else:
                person.contaminate_population()

        person.move()


def random_position():
    return np.array([randint(0,MAP_WIDTH), randint(0,MAP_HEIGHT)])

def random_direction():
    return np.array([randint(-10,10), randint(-10,10)])

def animate(i):
    colors = ["black", "red", "green"]
    scatters = []
    for health_state in range(3):
        positions = [data[i][j].position for j in range(len(data[i])) if data[i][j].health_state == health_state]
        x = [positions[j][0] for j in range(len(positions))]
        y = [positions[j][1] for j in range(len(positions))]

        scat = ax.scatter(x, y, c=colors[health_state])
        scatters.append(scat)

    return scatters



population = generate_population(50)

def main():
    ax.set(xlim=(0, MAP_WIDTH), ylim=(0, MAP_HEIGHT))

    data.append(deepcopy(population))

    for i in range(NB_CYLES):
        update_population()
        data.append(deepcopy(population))

  #  ani = animation.FuncAnimation(fig, animate,NB_CYLES, None, interval=dt*1000, blit=True, repeat=True)
    #Writer = animation.writers['ffmpeg']
    #writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)
    #ani.save("Video.mp4", writer="imagemagick")
  #  plt.show()


my_module.hi()
#main()
