Map = {
  name = "歪み電脳",
  wayMusic = "dhun",
  bossMusic = "",
  backgroundImage = "cyber_background.png",
  skin = "skinA",
  ending = "",
  nextMaps = {"3c_ocean","3d_space"},
  initialLevel = 11,
  maxLevel = 20,
  getEnemyTable = function(level)
    if level <= 20 then
      return {slime1T1 = 1} --歪み電脳の敵はすべて未実装
    elseif level <= 3 then
      return {}
    else
      return {}
    end
  end,
  getEnemyPopRate = function(level)
    return 0.6
  end,
  fixedEnemies = {
    --{"level10",0}
  }
}
