/**
 * Author: Aman Hogan-Bailey
 * Program implements breakout game as discussed in lecture.
 * The University of Texas at Arlington 5335
*/

var dx, dy; // displacement in x and y direction
var x, y; // x and y position
var score = 0; // number of games you played
var tries = 0; // number of times the ball missed the paddle
var started = false; // on whether game has started
var ball, court, paddle, brick, msg;
var court_height, court_width, paddleLeft;
var dt = 20; // Tick rate
var vx, vy; // velocity in x and y direction
var speed; // speed of the ball    
var angle; // random chosen angle of ball at start
var bricks = new Array(4);  // rows of bricks
var colors = ["red","blue","yellow","green"]; // colors of bricks
var brickWidth = 40;
var brickHeight = 21.25;
const baseSpeed = 350; // base speed of the game before lvl multiplier


/**
 * @desc The ball is relative to bottom left of court. 
 * The bricks are relative top right of court.
 * This converts brick coords to ball coords.
 * @param {brick[i]} brick the brick element
 * @returns left, top, right, and bottom coords of the brick.
 */
function convertCoords(brick)
{
    const courtRect = court.getBoundingClientRect();
    const brickRect = brick.getBoundingClientRect();

    const brickLeft = brickRect.left - courtRect.left;
    const brickTop = courtRect.bottom - brickRect.bottom;
    const brickRight = brickLeft + brickRect.width;
    const brickBottom = brickTop + brickRect.height;

    return { brickLeft, brickTop, brickRight, brickBottom };
}


/**
 * Gets element by id
 * @param {Element} s element 
 * @returns element
 */
function id(s) 
{
    return document.getElementById(s);
}


/**
 * Convert a string with px to an integer, eg "30px" -> 30
 * @param {*} pix  pixels
 * @returns an integer for pixels
 */
function pixels(pix) 
{
    return parseInt(pix.replace("px", ""), 10);
}


/**
 * Places the ball on top of the paddle
 */
function readyToKick()
{
    x = pixels(paddle.style.left) + paddle.width / 2 - ball.width / 2;
    y = pixels(paddle.style.top) + ball.height;
    ball.style.left = x + "px";
    ball.style.top = -y + "px";
}


/**
 * Paddle follows the mouse movement left-right
 */
function movePaddle(e)
{
    var ox = e.pageX - court.getBoundingClientRect().left;
    paddleLeft = Math.max(0, Math.min(court_width - paddle.width, ox));
    paddle.style.left = paddleLeft + "px";
    if (!started)
    {
        readyToKick();
    }
}

/**
 * Initializes court, ball, walls, and bricks
 */
function initialize() 
{
    court = id("court");
    ball = id("ball");
    paddle = id("paddle");
    wall = id("wall");
    msg = id("messages");
    brick = id("red");
    court_height = pixels(court.style.height);
    court_width = pixels(court.style.width);

    for (let i = 0; i < 4; i++) 
    {
        bricks[i] = new Array(20);
        let b = id(colors[i]);
        for (let j = 0; j < 20; j++)
        {
            let x = b.cloneNode(true);
            bricks[i][j] = x;
            x.style.left = 0 + 'px';
            x.style.top = 0 + 'px';
            wall.appendChild(x);
        }
        b.style.visibility = "hidden";
    }
    started = false;
}

/**
 * Sets the initial speed of the ball. Speed is determined by multiplying
 * 300 by the level number.
 */
function updateSpeed()
{
    const level = Number(document.getElementById("level").value);
    speed = baseSpeed * level;
}

/**
 * Updates the velocity of the ball
 */
function updateVelocity() 
{
    vx = speed * Math.cos(angle);
    vy = speed * Math.sin(angle);
}

/**
 * Updates angle of the ball
 */
function updateAngle() 
{
    angle = Math.random() * ((3 * Math.PI / 4) - (Math.PI / 4)) + (Math.PI / 4);
}

/**
 * Logs the kinematics of the ball for debugging purposes
 */
function logKinematics() 
{
    console.log(`Position: (x: ${x.toFixed(2)}, y: ${y.toFixed(2)})`);
    console.log(`Velocity: (vx: ${vx.toFixed(2)}, vy: ${vy.toFixed(2)})`);
    console.log(`Speed: ${speed.toFixed(2)}`);
    console.log(`Angle: ${angle.toFixed(2)} radians`);
}


/**
 * Updates the position of the ball using kinematic formula:
 * x = vx * dt
 * y = vy * dt
 * Checks for collisions collisions and updates position of ball on screen.
 */
function updatePosition() 
{
    x += vx * dt / 1000;
    y += vy * dt / 1000;

    handleCollisions();

    ball.style.left = x + "px";
    ball.style.top = -y + "px";
}

/**
 * Resets the ball after the ball misses the paddle
 */
function resetBall()
{
  tries = tries + 1;  
  started = false; 
  readyToKick();  
  console.log("Missed Paddle");
  id("tries").textContent = tries;
}


/**
 * Checks for collisions with top, left, right boundaries.
 * Checks for collisions with paddle and bricks.
 * Checks if ball missed paddle into bottom boundary.
 * Checks if all bricks have been cleared
 */
function handleCollisions()
{

    if(checkAllBricksCleared())
    {
        resetGame();
    }

    // Bottom boundary
    if (y <= 0 - ball.height) 
    {
        resetBall();
        return;
    }

    // Left and right boundary
    if (x <= 0 || x >= court_width - ball.width)
    {
        vx = -vx;
        x = Math.max(0, Math.min(x, court_width - ball.width));
        console.log("Hit left or right boundary");
    }

    // Top Boundary
    if (y >= court_height - ball.height)
    {
        vy = -vy; 
        console.log("Hit top boundary");
    }

    // Paddle Collisions
    const paddleTop = pixels(paddle.style.top);
    if (x + ball.width >= pixels(paddle.style.left) && x <= pixels(paddle.style.left) + paddle.width &&
        y + ball.height >= paddleTop && y <= paddleTop + paddle.height) 
    {
        
        // Only bounce ball if it is above paddle
        if (y + ball.height - vy * dt / 1000 >= paddleTop)
        {
            vy = -vy; 
            y = paddleTop + paddle.height;
            console.log("Hit paddle");
        }
    }

    // Brick Collisions
    for (let i = 0; i < bricks.length; i++)
    {
        for (let j = 0; j < bricks[i].length; j++)
        {
            const brick = bricks[i][j];
            if (brick && brick.style.visibility !== "hidden")
            {
                const { brickLeft, brickTop, brickRight, brickBottom } = convertCoords(brick);

                if (x + ball.width >= brickLeft && x <= brickRight && y + ball.height >= brickTop && y <= brickBottom)
                {
                    vy = -vy;
                    brick.style.visibility = "hidden";
                    console.log(`Hit brick ${i}-${j}`);
                    break;
                }
            }
        }
    }
}


/**
 * Reset game on click or after all bricks have been cleared. 
 * Resets tries but doesn't reset score.
 */
function resetGame() 
{
    score += 1; 
    tries = 0;
    id("score").textContent = score;
    id("tries").textContent = tries;
    resetBricks();
    readyToKick();
    started = false;
}


/**
 * Checks if all the bricks have been cleared or not
 * @returns bool - true or false of bricks have been cleared
 */
function checkAllBricksCleared() 
{
    for (let i = 0; i < bricks.length; i++)
    {
        for (let j = 0; j < bricks[i].length; j++)
        {
            if (bricks[i][j].style.visibility !== "hidden")
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * Resets the bricks back to visible
 */
function resetBricks()
{
    for (let i = 0; i < bricks.length; i++)
    {
        for (let j = 0; j < bricks[i].length; j++)
        {
            bricks[i][j].style.visibility = "visible";
        }
    }
}

/**
 * Starts the game. Runs game loop until a game ending condition is met.
 */
function startGame()
{
    if (!started) 
    {
        updateSpeed();  
        updateAngle();
        updateVelocity();
        updatePosition();
        started = true; 
        gameLoop();
    }
}

/**
 * Game loop that uses the tick/dt in set in the beginning.
 */
function gameLoop()
{
    if (started) 
    {
        updatePosition(); 
        // logKinematics();  
        setTimeout(gameLoop, dt); 
    }
}

