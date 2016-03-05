### Ancestral Roots
This is the first time I'm making a game for the 7 day roguelike challenge. I will try to document all the big design decisions I have made and I hope I will be able to finish the game. I am currently traveling in Laos so I won't be able to spend too much time on it every day. I will start at 12:00 local time on Saturday the fifth, and hopefully have a finished game after exactly 168 hours.

### About the game
You will play as a proud warrior of a tribe somewhere in the bronze age, you are the descendant of a long lineage of warriors. You ancestors have fought with other tribes for generations, so the relationships between your tribe and other tribes might not be all peacelike and friendly.
## Mechanics
# Dying
When you die you will respawn as a direct descendant of your previous character. Some of the skills you have will be persistent, and the relationships between the different tribes will also be persistent. What's non persistent is the world.
# Relationships between tribes
The relationships between tribes are a scale from positive (allies) to negative (enemies), when you kill a member of a tribe the scale of that tribe and the allied tribes will go down a bit, and the scale of the enemy tribes will go up.

### Day 1
## Implementation details
The game will be written in C and Lua-5.3, I will use the [ccore](http://github.com/ccore/ccore) library to use the OpenGL interface and input handling.
