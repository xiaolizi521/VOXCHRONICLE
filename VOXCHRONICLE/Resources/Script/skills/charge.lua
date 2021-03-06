Skill = {
  name = "ＭＰリカバリー",
  identifier = "charge",
  mp = 0,
  tensionLevel = 0,
  effectFrames = 0,
  common = false,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 1,
  se = true,
  turn = 1,
  loop = true,
  canRepeat = true,
  keepTension = false,
  performSkill = function(self, target, characterManager, enemyManager)
    local tension = characterManager:getTension() -- テンションをとって
    local power = self:getPower(characterManager) -- パワーとって
    local rate = power / 10.0 -- 割合出して
    local max = characterManager:getMaxMP() -- 最大値出して
    local cure = power
    characterManager:addMP(cure) -- 回復させる
    EffectLayer:sharedLayer():addDamageLabel(-cure, 0, DamageLabelTypeMPCure)
  end,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {1, 2, 4, 6, 8}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  getMessageTable = function(self, targets, map, characterManager, enemyManager)
    local mp = characterManager:getMP()
    local maxMP = characterManager:getMaxMP()
    if mp == maxMP then
      return { -- 魔力最大なのに使ったとき
        "もう　はいらないよぉ",
        "ラスカの　まりょくは　すでにいっぱいだ",
        "まりょくは　すでにさいだいだ",
        "すでに　さいだい　です",
      }
    end
    return { -- 通常時
      "オクスは　ラスカに　まりょくをそそぎこんだ",
      "ラスカの　まりょくをかいふくさせた",
      "まりょくを　じゅうてんした",
      "まりょくが　みちていく",
      "ラスカのＭＰが　かいふくした",
      "ラスカの　ちからが　かいふくした",
    }
  end
}
