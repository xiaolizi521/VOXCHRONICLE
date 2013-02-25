-- 召喚技
EnemySkill = {
  name = "なかまをよぶ",
  performSkill = function(self, user, characterManager, enemyManager)
    local species = user:getIdentifier()
    local row = user:getRow()
    local col = user:getCol()
    local newCol = (col + math.random(0, 1)) % 3
    local enemy = enemyManager:popEnemyAt(species, row, newCol)
    local mManager = MessageManager:shaderManager()
    mManager:pushMessage(user:getName().."は　なかまを　よんだ")
    mManager:pushMessage(enemy:getName().."が　あらわれた！")
  end
}
return EnemySkill
