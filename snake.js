import { pauseResumeGame } from "./main.js"

let rangeSize = document.querySelector('#screenSizeRange')
let screenSize = setScreenSize(parseInt(rangeSize.value))
let rangeSpeed = document.querySelector('#gameSpeedRange')
export let gameSpeed = setGameSpeed(parseInt(rangeSpeed.value))

const screen = document.querySelector('.gameboard')
let foodElement = document.createElement('div')
const snakeHead = document.createElement('div')
const highscore = document.querySelector('.highscore span')
let highscoreCount = 0
const score = document.querySelector('.score span')
let scoreCount = 0
const round = document.querySelector('.round span')
let roundCount = 1
let foodPos = 0
let direction = 0
let lastdirection = 0
export const snakeBody = new Array()

export function init() {
  /* Reset */
  screen.innerHTML = ""
  foodPos = 0
  direction = { x: 0, y: 1 }
  lastdirection = direction
  snakeBody.length = 0
  scoreCount = 0
  screen.style.gridTemplateColumns = `repeat(${screenSize}, 1fr)`
  screen.style.gridTemplateRows = `repeat(${screenSize}, 1fr)`
  /* End Reset */

  snakeBody.push({ x: Math.floor(screenSize / 2), y: Math.floor(screenSize / 2), bodyPartDirection: "0turn" })
  setFoodPos()

  foodElement.classList.add('food')
  foodElement.style.gridColumnStart = foodPos.x
  foodElement.style.gridRowStart = foodPos.y
  screen.appendChild(foodElement)

  snakeHead.classList.add('snake', "snakeHead")
  snakeHead.style.gridColumnStart = snakeBody[0].x
  snakeHead.style.gridRowStart = snakeBody[0].y
  screen.appendChild(snakeHead)

  if (scoreCount >= highscoreCount) {
    highscoreCount = scoreCount
    highscore.textContent = highscoreCount
  }
  score.textContent = scoreCount
  round.textContent = roundCount++
}

function setFoodPos() {
  foodPos = getRandomPos()
  if (onSnakeHead())
    setFoodPos()
}


/* functions */

export function drawSnake() {
  SnakeMove()
  snakeHead.style.gridColumnStart = snakeBody[0].x
  snakeHead.style.gridRowStart = snakeBody[0].y
  snakeHead.style.rotate = snakeBody[0].bodyPartDirection
}

function SnakeMove() {
  let snake = document.querySelectorAll('.snake')
  for (let i = snakeBody.length - 1; i >= 1; i--) {
    snakeBody[i] = { ...snakeBody[i - 1] }
    snake[i].style.gridColumnStart = snakeBody[i].x
    snake[i].style.gridRowStart = snakeBody[i].y
    snake[i].style.rotate = snakeBody[i].bodyPartDirection
  }
  snakeBody[0].x += direction.x
  snakeBody[0].y += direction.y
  if (snakeBody[0].x == screenSize + 1) snakeBody[0].x = 1
  else if (snakeBody[0].x == 0) snakeBody[0].x = screenSize
  if (snakeBody[0].y == screenSize + 1) snakeBody[0].y = 1
  else if (snakeBody[0].y == 0) snakeBody[0].y = screenSize
}


export function addBody() {
  score.textContent = ++scoreCount
  document.querySelector('#scoreGameEnd span').textContent = scoreCount
  if (scoreCount >= highscoreCount) {
    highscoreCount = scoreCount
    highscore.textContent = highscoreCount
  }
  let x = snakeBody[snakeBody.length - 1].x
  let y = snakeBody[snakeBody.length - 1].y
  let turnDirect = snakeBody[snakeBody.length - 1].bodyPartDirection
  snakeBody.push({ x: x, y: y, bodyPartDirection: turnDirect })

  let snakeBodyPart = document.createElement('div')
  snakeBodyPart.classList.add('snake', "snakeBody")
  snakeBodyPart.style.gridColumnStart = x
  snakeBodyPart.style.gridRowStart = y
  snakeBodyPart.style.rotate = turnDirect
  screen.appendChild(snakeBodyPart)
}

export function placeFood() {
  foodPos = getRandomFoodPos()
  foodElement.style.gridColumnStart = foodPos.x
  foodElement.style.gridRowStart = foodPos.y
}

function getRandomFoodPos() {
  foodPos = getRandomPos()
  while (onSnakeHead() || intersection(foodPos))
    foodPos = getRandomPos()
  return foodPos
}

function getRandomPos() {
  return {
    x: Math.floor(Math.random() * screenSize) + 1,
    y: Math.floor(Math.random() * screenSize) + 1
  }
}

export function intersection(obj) {
  for (let i = snakeBody.length - 1; i >= 1; i--) {
    if (obj.x == snakeBody[i].x && obj.y == snakeBody[i].y)
      return true
  }
  return false
}

export function onSnakeHead() {
  return snakeBody[0].x == foodPos.x && snakeBody[0].y == foodPos.y
}

document.addEventListener('keydown', keyListener)
function keyListener(e) {
  e.preventDefault()
  console.log(e.key);
  let bl = snakeBody.length == 1
  switch (e.key) {
    case 'ArrowUp':
      if (lastdirection.y != 1 || bl) {
        direction = { x: 0, y: -1 }
        snakeBody[0].bodyPartDirection = ".5turn"
      }
      break
    case 'ArrowDown':
      if (lastdirection.y != -1 || bl) {
        direction = { x: 0, y: 1 }
        snakeBody[0].bodyPartDirection = "0turn"
      }
      break
    case 'ArrowRight':
      if (lastdirection.x != -1 || bl) {
        direction = { x: 1, y: 0 }
        snakeBody[0].bodyPartDirection = "-.25turn"
      }
      break
    case 'ArrowLeft':
      if (lastdirection.x != 1 || bl) {
        direction = { x: -1, y: 0 }
        snakeBody[0].bodyPartDirection = ".25turn"
      }
      break
    case "p":
      toggleMenu(2)
      pauseResumeGame()
      break
    case "P":
      toggleMenu(2)
      pauseResumeGame()
      break
    default:
      break
  }
  lastdirection = direction
}

export function limitOfBodiesReached() {
  return snakeBody.length == screenSize * screenSize - 1
}

/* Screen Size Range */

document.querySelector('.size-label span').textContent = screenSize + "x" + screenSize
rangeSize.addEventListener("input", e => {
  screenSize = setScreenSize(parseInt(e.target.value))
  document.querySelector('.size-label span').textContent = screenSize + "x" + screenSize
  init()
})

function setScreenSize(size) {
  let n = 15
  switch (size) {
    case 1 || "1":
      n = 10
      break
    case 2:
      n = 15
      break
    case 3:
      n = 20
      break
    case 4:
      n = 25
      break
    case 5:
      n = 30
      break
    case 6:
      n = 35
      break
    case 7:
      n = 40
      break
    case 8:
      n = 45
      break
    default:
      break
  }
  return n
}

document.querySelector('.speed-label span').textContent = gameSpeed + "ms/frame"
rangeSpeed.addEventListener("input", e => {
  gameSpeed = setGameSpeed(parseInt(rangeSpeed.value))
  document.querySelector('.speed-label span').textContent = gameSpeed + "ms/frame"
})

function setGameSpeed(speed) {
  let n = 50
  switch (speed) {
    case 1:
      n = 200
      break
    case 2:
      n = 150
      break
    case 3:
      n = 100
      break
    case 4:
      n = 50
      break
    case 5:
      n = 25
      break
    case 6:
      n = 10
      break
    case 7:
      n = 1
      break
    default:
      break
  }
  return n
}

export function toggleMenu(n) {
  let menu = document.querySelectorAll('.menu')
  menu[n].classList.toggle("show")
  document.querySelector('.backlay').classList.toggle("show")
}