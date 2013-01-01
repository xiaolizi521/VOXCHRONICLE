-- ナイト用溜め攻撃
EnemySkill = {
  name = "強攻撃",
  performSkill = function(self, user, characterManager, enemyManager)
    local key = "swordTurn"
    local turn = user:getRegister(key, 0) -- 溜めているターンを取得
    if turn == 0 then
      -- 溜め初回ターンの時
      -- user:setAnimationClip("sword") -- グラを変更する
      user:setRegister(key, turn + 1)
    elseif turn == 2 then
      -- 溜めターンが2ターンに到達したら溜め攻撃発動
      characterManager:damage(5) -- ダメージを与える
      user:setRegister(key, 0) -- 溜めターンをリセット
      -- user:setAnimationClip("walk") -- グラを元に戻す
    else
      user:setRegister(key, turn + 1) -- ターンを+1する
    end
  end
}
return EnemySkill