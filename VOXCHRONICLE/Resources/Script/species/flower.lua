Enemy = {
  name = "パンジーさん",
  imageName = "flower",
  attack = 2,
  baseExp = 3,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    local row = enemy:getRow()
    local rand = math.random(3)
    if rand == 1 then
    rand = math.random(4)
    end
    if row >= 6 then
      return 1
    elseif row <=1 then
      return rand - (4 - row)
    end
    return rand - 2
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {},
  description = [[
ハミングしていないと光合成できないので、常にハミングしている。最近のパンジーさん界隈ではボッサがきてる。
生息地：平原ほか　攻撃力：ふつう　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(enemy,self)
    local row = enemy:getRow()
    --[[ local col = user:getCol()
        col = math.random(2) - 1 - col
    user:setCol(col)
]]
    local rand = math.random(5)
    if row == 0 and rand <= 3 then
        return "direct_attack"
    end
    return ""
  end
}

return Enemy