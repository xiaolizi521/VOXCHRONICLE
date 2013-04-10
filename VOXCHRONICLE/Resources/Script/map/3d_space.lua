Map = {
  name = "惑星外宙域S-B-α",
  wayMusic = "nmb",
  bossMusic = "AttaQ3-D",
  ending = "",
  skin = "skinA",
  introCount = 0,
  backgroundImage = "3d_background0.png",
  thumbnailImage = "space_thumbnail.png",
  nextMaps = {},
  initialLevel = 25,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level <= 22 then
      return {exob3D5 = 3, t2pha3D1 = 4}
    elseif level <= 24 then
      return {planet3D0 = 1, t2pha3D1 = 3}
    elseif level <= 29 then
      return {exob3D5 = 1, planet3D0 = 1, t2pha3D1 = 1}
    end
    return {}
      --return {exob3D5 = 3, planet3D0 = 1, t2pha3D1 = 1, whale3D7 = 1}
  end,
    onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("t2pha.png")
    enemyManager:loadEnemyTextureAsync("exob.png")
    enemyManager:loadEnemyTextureAsync("planet.png")
    enemyManager:loadEnemyTextureAsync("fortress.png")
    enemyManager:loadEnemyTextureAsync("knight.png")
    
    enemyManager:loadEnemyTextureAsync("kraken_body.png")
    enemyManager:loadEnemyTextureAsync("R_strfoot.png")
    enemyManager:loadEnemyTextureAsync("R_plfoot.png")
    enemyManager:loadEnemyTextureAsync("R_plclaw.png")
    enemyManager:loadEnemyTextureAsync("R_strclaw.png")
    enemyManager:loadEnemyTextureAsync("L_strfoot.png")
    enemyManager:loadEnemyTextureAsync("L_plfoot.png")
    enemyManager:loadEnemyTextureAsync("L_plclaw.png")
    enemyManager:loadEnemyTextureAsync("L_strclaw.png")
  end,
    onBack = function(self, characterManager, enemyManager)
    local enemies = enemyManager:getEnemies()
    local enemyCount = enemies:count()
    local level = characterManager:getLevel()
    if level >= 25 then
      if enemyCount == 0 then
        enemyManager:popEnemyAt("planet15_3D0", 7, 1)
      end
    end
  end,
  
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 25 then
      enemyManager:popEnemyAt("planet15_3D0", 7, 1)
    elseif level == 26 then
      enemyManager:popEnemyAt("fortress3D0", 7, 1)
      enemyManager:popEnemyAt("knight3D1", 7, 0)
      enemyManager:popEnemyAt("knight3D2", 7, 2)
    elseif level == 27 then
      enemyManager:popEnemyAt("fortress3D0", 7, 0)
      enemyManager:popEnemyAt("fortress3D0", 7, 2)
    elseif level == 28 then
      enemyManager:popEnemyAt("kraken3D0", 7, 0)
      enemyManager:popEnemyAt("R_strfoot3C0", 4, 2)-- 足
      enemyManager:popEnemyAt("L_plfoot3C0", 4, 0)
      enemyManager:popEnemyAt("R_plfoot3C0", 3, 2)
      enemyManager:popEnemyAt("L_strfoot3C0", 3, 0)
      enemyManager:popEnemyAt("R_strclaw3C0", 2, 2)
      enemyManager:popEnemyAt("L_plclaw3C0", 2, 0)
      enemyManager:popEnemyAt("R_plclaw3C0", 1, 2)
      enemyManager:popEnemyAt("L_strclaw3C0", 1, 0)
    elseif level == 29 then
      enemyManager:popEnemyAt("planet15_3D0", 7, 1)
    end
  end,
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    data:unlockAchievement("clear3D")
  end,
  getEnemyPopRate = function(level)
    if level >= 25 then
    return 0
    end
    return 0.3
  end
}

