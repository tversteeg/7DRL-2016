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
## Status
I implemented some very rudimentary "class" system, where there are multiple tribes each with a list of humans, the player itself is a "subclass" of a human. Humans themselves have a stats object. (I put "classes" in quotes because Lua doesn't support any real OOP-like classes). 

## Story time
I haven't spend as much time as I would like to have spend, but my first day was a really chaotic one for me. I am staying at a hostel in Vientiane (Laos), and I was planning on going out for dinner with my motorbike. When I drove my motorbike of the property where I was staying there was a guy with a broken foot talking to a tuktuk driver, I have talked to him before but I didn't really know why his foot was broken. I offered him a ride on the back of my motorbike, and he asked me to drive past a group of "friends" in the alley just 20 meters from where I was standing; I thought he just wanted to say hello so I drove past them with him. They stared at us strangely but I didn't really think much of it. He asked me to turn around and drive back past them, when I did this they made some symbol on the road with a stick and a leaf; I stopped to watch what they were doing but the American guy urged me to go on. I dropped him of at the hostel and went for dinner.

When I got back I talked to him, and he explained me that these guys were not his friends but are part of some gang he had a fight with, he told me that he started the fight because a tuktuk driver tried to rip him of. According to him they tried to bash his head in with a boulder, broke his foot, climbed into his hotel (the previous one) to fight him and flash a machine gun at him to scare him. Needless to say I was pretty scared after that because I just drove past the gang with him on the back of my motorbike, stopped in front of them and turned around. I hope they don't associate me with him and to be sure I won't leave the hostel today.. After that I couldn't really bring myself back to continue programming. I hope day 2 will be a better day.
