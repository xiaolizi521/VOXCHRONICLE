--[[
 スキルトリガーの配置データ
 x : x座標の配置データを持たせてください
 y : y座標
 scale : トリガーの大きさ0~1
 rotation : トリガーの回転角 0~360
 ]]--

Type0 = { -- 初期バージョン
  x = {51.0, 38.0, 110.2, 130.5, 341.8, 375.2, 443.2, 410.2},
  y = {52.2, 129.2, 107.8, 38.2, 50.8, 111.2, 111.2, 52.0},
  scale = {0.492, 0.376, 0.376, 0.376, 0.376, 0.376, 0.376, 0.376},
  rotation = {45.0, 45.0, 45.0, 45.0, 90, 90, 90, 90}
}

Type1 = { -- 横に配置バージョン
  x = {42, 42, 42, 42, 445, 445, 445, 445},
  y = {42, 110, 175, 240, 35, 100, 165, 230},
  scale = {0.40, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35},
  rotation = {0, 0, 0, 0, 0, 0, 0, 0}
}

return Type1 -- 採用する配置タイプを返してください