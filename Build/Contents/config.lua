local config = class("config")

function config:config()
	self.game_speed = 0 -- �[���\�е��ٶ�	
	self.player_move_speed = 20 --���﹥���ĕr��ÿ���r�gƬ�Ƅӵ��ٶ�
	self.enemy_move_speed = 30 --С�����Ƅӵ��ٶȣ��̶����x���Ƅӵ��ٶȣ����磬���ﱻ�����ˣ�ͬһ�������С����Ҫ�����100�ľ��x�ٶ�
	self.player_attack_miss_move_dst = 50 --���﹥��miss����ǰ���ӵľ��x
	self.palyer_be_acctacted_move_speed = 5 --���ﱻ�����ĕr������Ƅӵ��ٶ�
	self.left_attack_area = 350 --��߅�Ĺ���^����x
	self.right_attack_area = 350 --��߅�Ĺ���^����x
	self.player_attack_dst = 140 --���﹥��С���ľ��x
	self.enemy_attack_dst = 100 --С����������ľ��x
	self.enemy_before_attack_dst = 120 --С����������ľ��x
	self.attack_pause_time = 10 --�����С���Ĺ�����ͣ�D�r�g
	self.attack_pause_delay = 3 --�����С���Ĺ���ͣ�D�r�g�ӕr��λ ���w��Ӌ����ÿ2���r�gƬ�͈���һ�Σ����0��ʾ���ӕr
	self.move_distance = 50 -- С�������˺���������������С�����Ƅӵľ��x
end