Map = {
  name = "テストマップ",
  prefix = "dub",
  backgroundImage = "",
  nextMaps = {"test", "test"},
  initialLevel = 1,
  getEnemyTables = function(level)
    enemies = {}
    if true then
      enemies = {tnt = 30}
    end
    return enemies
  end
}
