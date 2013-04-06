Map = {
  name = "草原",
  wayMusic = "volca",
  bossMusic = "",
  backgroundImage = "field_background0.png",
  skin = "skinB",
  ending = "",
  nextMaps = {"2b_cave","2c_cyber"},
  initialLevel = 1,
  maxLevel = 10,
  onLoad = function(self, characterManager, enemyManager)
    local time = VQTime:sharedTime()
    local hour = time:getCurrentHour()
    local number = 0
    if 6 <= hour and hour < 16 then
      number = 0
    elseif 16 <= hour and hour < 19 then
      number = 1
    else
      number = 2
    end
    local imageName = "field_background"..number..".png"
    self:changeBackgroundImage(imageName)
    
  end,
  getEnemyTable = function(level)
    if level <= 2 then
--return {}
      return {slime1B7 = 3, moth1B0 = 2}
    elseif level <= 4 then
      return {flower1B0 = 1, moth1B0 = 5}
    elseif level <= 6 then
      return {flower1B0 = 1, hornet1B1 = 1}
    elseif level <= 8 then
      return {slime1B7 = 1, flower1B0 = 1, moth1B0 = 2}
    elseif level <= 10 then
      return {slime1B7 = 1, flower1B0 = 1, moth1B0 = 1, hornet1B1 = 1}
    end
    return {slime1B7 = 1, flower1B0 = 1, moth1B0 = 1, hornet1B1 = 1}
  end,
  onLevelUp = function(self, characterManager, enemyManager)
  end,
  getEnemyPopRate = function(level)
    if level <= 2 then
      return 0.3
    elseif level <= 4 then
      return 0.4
    elseif level <= 6 then
      return 0.2
    elseif level <= 8 then
      return 0.3
    elseif level <= 10 then
      return 0.3
    end
    return 0.2
  end,
  fixedEnemies = {
    {"flower1B0",0}
  }
}
