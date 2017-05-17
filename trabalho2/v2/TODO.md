# TODO List

*  ### **Increase speed of invaders' movement**
 	Besides of moving invaders to the left and right, it would be interesting to increase the speed of movement as it gets closer to the bottom ref: http://www.clickjogos.com.br/Jogos-online/Tiro/Space-Invaders/

* ### **Draw a more nice looking base airship.**
	 Draw the base airship like version 1?
	 Will need to update collision check to consider new base airship.

* ### **GameOver**
	Create a restart option?
	Send the player a message?
		* YOU LOST - GAME OVER
		* YOU WIN - NEXT PHASE
	Go to a harder phase if it's a win??
		* increase speed of invaders movement
		* invaders starting from a lower Y position
		* increase number of lifes necessary to kill a invader
	
* ### **Invaders' shooting randomly**
 	Try different timers and different approaches for random generation of coordinates. Maybe give more probability to the area the base is in.

* ### **SPACE key pressing independently of RIGHT/LEFT**
	Differentiate when a key is pressed down and when it keeps being pressed. This will allow the base airship to move independently of the bullets.
	When a player press and holds RIGHT or LEFT and then shoots with space, it's necessary to press RIGHT or LEFT again in order to keep the airship moving. The idea here is to make these key pressing independently.

* ### **Update world's coordinates when window is resized**
	Maybe it'll be necessary to keep these values as initial and change it if the window is resized. In that case, we'll need to replace the usages of fixed values considering the variables with current sizes
