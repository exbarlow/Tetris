
1. The player will control the blocks with the arrow keys

Test by playing; alternatively could look at the first test in model_test.cxx or the shift_right() and shift_left() functions in model.cxx
Available immediately after loading game

2. The player will be able to store one block with the "C" key -- however, they cannot store two blocks in a row, they must wait for another block to fall

Test by playing;
Available immediately after loading game
To clarify -- you cannot swap blocks back and forth, or swap the first and second block of the game

3. The player will be able to rotate the block with the up key, as long as the rotated block will not go out of bounds or hit a fixed block'

Test by playing;
Available immediately after loading game

4. The player will be able to fast drop the block with the spacebar

Test by playing;
Available immediately after loading game

5. The next three blocks will be shown to the player

Test by playing;
Available immediately after loading game

6. The stored block will be shown to the player.

Test by playing;
Available immediately after loading game

7. If the blocks cover a full row, then that row will be deleted and points will be added to the player's score

Test by playing;
Align blocks such that they cover a full row to see this happen

8. If the blocks reach the top border such that they block an upcoming block from falling into the visible screen, the game will end and a game over screen will display, including the player's score.

Test by playing;
The fastest way to do this is to press the space bar repeatedly

9. The blocks will fall slowly from the top of the screen (with the first falling after an initial delay), gradually increasing in speed as the player's score increases

Test by playing;
Available immediately after loading game

10. The player's score will be displayed in real time both during the game and after the game ends.

Test by playing;
Available immediately after loading game -- also check that it displays after by ending the game (see comments on 8)

11. A phantom outline will appear at the bottom of the screen, showing where the block will fall if the spacebar is pressed or if it is left to fall

Test by playing;
Available immediately after loading game

12. The player can press the down key to accelerate downward movement and gain points.

Test by playing;
Available immediately after loading game
One point is gained for every downward movement -- you can hold down the button too.