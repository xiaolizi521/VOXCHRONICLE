Enemy = {
  name = "リスタルク",
  imageName = "cryst",
  attack = 8,
  baseExp = 1,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
気の遠くなるような年月を経て力を持った結晶石。
自分の生まれた場所を守ろうとしている。
生息地：炭鉱ほか　攻撃力：そこそこ　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy