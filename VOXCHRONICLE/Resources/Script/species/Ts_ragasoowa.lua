Enemy = {
  name = "ラガスーワ",
  imageName = "ragasoowa",
  attack = 0,
  baseExp = 0,
  hasFrame = false,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {},
  description = [[
たわしさんまかせた
]],
  habitat = "",
  animationFrames = 5,
  performSkill = function(self)
  return ""
  end
}

return Enemy