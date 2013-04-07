Map = {
  name = "Lesson2",
  wayMusic = "chabo",
  bossMusic = "",
  backgroundImage = "simple_background.png",
  skin = "skinA",
  ending = "",
  nextMaps = {},
  initialLevel = 11,
  maxLevel = 21,
  getEnemyTable = function(level)
    return {}
  end,
   onBack = function(self, characterManager, enemyManager)
    math.random(100)
    local layer = EffectLayer:sharedLayer()
    local preHP = self.__IRegister__:getRegister("preHP", characterManager:getHP())  
    local level = characterManager:getLevel()
    local enemies = enemyManager:getEnemies()
    local enemyCount = 0
    if not (enemies == nil) then
      enemyCount = enemies:count()
    end
    if level == 11 then
      -- ラスカにチェンジしないと先には進めない
      if characterManager:getCurrentCharacter():getName() == "ラスカ" then
      	-- ラスカにチェンジ済なので、敵が1体もいなくなったらモンスター生成
      	if enemyCount == 0 then
          enemyManager:popEnemyAt("T_slime30", 3, 1)
      	end
      end
    elseif level == 12 then
      -- 敵が1体もいなくなったらモンスター生成
      if enemyCount == 0 then
          enemyManager:popEnemyAt("T_moth7", 5, 0)
          enemyManager:popEnemyAt("T_moth7", 5, 1)
          enemyManager:popEnemyAt("T_moth7", 5, 2)
          enemyManager:popEnemyAt("T_moth7", 5, 3)
      end
    end
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    self.__IRegister__:clearRegister()
    local level = characterManager:getLevel()
    local layer = EffectLayer:sharedLayer()
    if level == 11 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "ラスカにチェンジ！", [[
さぁ！ラスカちゃんに注目が集まるチュートリアルBよ！そろそろオクス君も疲れたでしょうから、私とタッチ交代してみて。新しくチェンジコマンドが追加されてるからタッチして私に交代してちょうだい。音楽も変わって気分一新よ！

私、ラスカは魔法使い。オクス君は剣だけど私は杖で氷結魔法を使って攻撃するわ。基本はオクス君と操作は変わらないから色々試してみてね！
]])
    elseif level == 12 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "MPに注意！", [[
私、ラスカは魔法使い！　…なんだけれど、魔法使いの宿命として特殊な行動にはMPを消費しちゃうのよねぇ。これから説明する範囲攻撃、弓攻撃、回復魔法を使うときはMPを消費するからMP切れには注意してね！
]])
      popup:setText(1, "必殺！ラスカサンダー！", [[
さて軍団が攻めてくるわ！オクス君の時と同じように、テンション溜めながら敵を引きつけて、範囲攻撃の必殺！ラスカサンダー！で一気に倒しちゃいましょう。オクススラッシュとは違ってMPを消費しちゃうので気をつけてね。

あ、MP切れそうだったけれどいつの間にか回復してる！オクス君でしょ、気が利くわねぇ！
]])
	elseif level == 13 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "魔法弓で狙い撃ち！", [[
オクス君はノックバックが使えてたけれど、私は魔法弓で遠距離攻撃が出来るのよ！通常だと最前列の敵が攻撃対象だけれど、魔法弓攻撃だと画面上で一番HPの高い敵に攻撃できるわ。

威力も高めだし、ボス戦とかで重宝するかもね！他には倒せない敵が最前列に来たときとかかしら。けれどこれもMP消費するから注意して使ってね。
]])
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
