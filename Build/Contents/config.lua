local config = class("config")

function config:config()
	self.game_speed = 0 -- 遊戲運行的速度	
	self.player_move_speed = 20 --人物攻擊的時候每個時間片移動的速度
	self.enemy_move_speed = 30 --小兵的移動的速度，固定距離下移動的速度，比如，人物被攻擊了，同一個方向的小兵需要向后退100的距離速度
	self.player_attack_miss_move_dst = 50 --人物攻擊miss后往前滑動的距離
	self.palyer_be_acctacted_move_speed = 5 --人物被攻擊的時候向后移動的速度
	self.left_attack_area = 350 --左邊的攻擊區域距離
	self.right_attack_area = 350 --右邊的攻擊區域距離
	self.player_attack_dst = 140 --人物攻擊小兵的距離
	self.enemy_attack_dst = 100 --小兵攻擊人物的距離
	self.enemy_before_attack_dst = 120 --小兵攻擊人物的距離
	self.attack_pause_time = 10 --人物和小兵的攻擊總停頓時間
	self.attack_pause_delay = 3 --人物和小兵的攻擊停頓時間延時單位 具體的計算是每2個時間片就執行一次，等於0表示不延時
	self.move_distance = 50 -- 小兵攻擊人后，人物和人物後面的小兵都移動的距離
end