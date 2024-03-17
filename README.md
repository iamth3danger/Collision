# 2D Collision Simulator
![](../master/Images/2dCollision.gif)


In this project, I make a simulation of collisions of 2 dimensions with squares. I used SDL2 to animate and implement the game loop. SDL2 made both animating and rendering a relatively straight forward process. The hardest part of this was implementing the physics, using the write 
equations and making efficient collision detection. For the physics I worked with two equations. !(../master/Images/2dCollision.svg) This equation worked, but was hard to implement because of gamma. Gamma is the angle of collision and it was difficult to find a formula for it. I was 
never sure that my collisions where correct and I ended up using it for too long. Also the equation would put out insane numbers if I was using atan instead of atan2 and I have no idea why. The better collision formula for this case is !(../master/Images/anglessCollision.svg) 
This equation has no angles and makes the code shorter and easier to read. There is no need for angles to be input or output so getting rid of them makes everything clearer.

The other big part of this project was getting the collision detection correct. I was using AABB collision detection. It works by having one square check if the other square is above, below, to the left, and to the right of it. If the other square fails one of these checks the
function returns that it's in a collision. This works, but it also has its own drawbacks. One is that everything has to be a square and all of the lines have to be parallel to the other lines. Meaning that you cant have a rotating square with AABB. Also because this checks collision 
twice per frame, there's an issue with tunneling. The square won't know it's in a collision until its already inside the other square. This can cause an endless feedback loop of collisions from reversing directions. My solution was to create a static std::vector in my platform class
that would keep track with what collided with what. So when square A collides with square B the vector will add the string "A collided with B" and then check if the last collision was "A collided with B" or "B collided with A". I also had a boolean that said whether the square was
in a collision or not. This did help a lot, but unfortunately it still happens.

I want to implement continuous collision detection that would predict when and where the collision would happen so I don't have the tunneling issue anymore. I would also like to figure out how to solve three or more objects colliding with eachother at the same time. I think implementing
these two things would make my program look a lot cleaner and smoother.
