import { drawSnake, init, addBody, placeFood, onSnakeHead, intersection, limitOfBodiesReached, snakeBody, gameSpeed, toggleMenu } from './snake.js'

let timer = 0
let gamePaused = false
async function GameFrame() {
  drawSnake()
  if (intersection(snakeBody[0])) {
    toggleMenu(1)
    return
  }
  else if (onSnakeHead()) {
    addBody()
    placeFood()
  }
  else if (limitOfBodiesReached()) {
    window.alert("You won!")
    return
  }
  Sleep(gameSpeed).then(() => {
    requestAnimationFrame(GameFrame)
  })
  return
}

export function pauseResumeGame() {
  if (!gamePaused) {
    gamePaused = !gamePaused
    clearTimeout(timer)
  }
  else {
    gamePaused = !gamePaused
    window.requestAnimationFrame(GameFrame)
    clearTimeout(timer)
  }
}

document.addEventListener("click", e => {
  switch (e.target.id) {
    case "startGameBtn":
      toggleMenu(0)
      init()
      window.requestAnimationFrame(GameFrame)
      break
    case "playAgainBtn":
      toggleMenu(1)
      init()
      window.requestAnimationFrame(GameFrame)
      break
    case "resumeBtn":
      toggleMenu(2)
      pauseResumeGame()
    default:
      break
  }
})

function Sleep(millisec) {
  return new Promise(res => {
    timer = setTimeout(res, millisec)
  })
}
