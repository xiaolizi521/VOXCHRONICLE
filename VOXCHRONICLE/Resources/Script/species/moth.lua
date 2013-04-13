Enemy = {
  name = "チョウゥチョ",
  imageName = "moth",
  attack = 5,
  baseExp = 10,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    return 1

  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
  ポンポンの粉を散らされると死んでしまう儚い命。ジクーの天敵。
  稀に集団発生してはオクスとラスカと誰かを大いに苦しめる。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy