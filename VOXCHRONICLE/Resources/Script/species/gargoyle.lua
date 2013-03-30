Enemy = {
  name = "ガーゴイル",
  imageName = "gargoyle",
  attack = 12,
  baseExp = 10,
  hasFrame = true,
  counter = 3,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
  がーごいる　がー　がー　あひるじゃないよ　いわだよ
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy