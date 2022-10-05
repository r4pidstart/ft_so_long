# so_long - And thanks for all the fish!

### This project’s objectives are similar to all this first year’s objectives: Rigor, use of C, use of basic algorithms, information research etc. As a graphic design project, so long will enable you to improve your skills in these areas: windows, colors, events, textures, etc.
*Version : 1*

---

#### Mandatory part
##### Program name
* so_long
##### External functs. 
* open, close, read, write,
printf, malloc, free, perror,
strerror, exit
* All functions of the MinilibX
##### Description
* You must create a small 2D game where a dolphin
escapes earth after eating some fish. Or any hero
collects any valuables before leaving the place.

#### Bonus part
* enemy patrols that cause the player to lose in case of contact.
* There’s some sprite animation.
* Movement count is directly displayed on the screen instead of shell output.

---

이 밑은, 각 함수에 대해서, 간략하게 해당 함수의 코드와 함께 정리한 내용들입니다.
함수의 순서는 호출 순서입니다.

<details>
    <summary>int	main(int argc, char **argv)</summary>
  
```c
typedef struct s_vars
{
	void		*m;
	void		*w;
	char		**table;
	t_map		map;
	t_assets	assets;
}t_vars;

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		return (!printf("Wrong argument\n"));
	else if (verify_map(argv[1], &vars.map))
		return (1);
	vars.table = make_table(&vars.map);
	if (!vars.table)
	{
		free_elements(&vars);
		return (2);
	}
	vars.m = mlx_init();
	vars.w = mlx_new_window(vars.m, vars.map.col * 64, vars.map.row * 64, \
		"so_long");
	vars.assets = get_assets(&vars);
	draw_image(&vars, 0);
	mlx_hook(vars.w, 2, 0, key_hook, &vars);
	mlx_hook(vars.w, 17, 0, close_game, &vars);
	mlx_loop_hook(vars.m, loooooop, &vars);
	mlx_loop(vars.m);
}
```
* 인자를 확인하고, 받아온 지도가 멀쩡한지 확인합니다.
* 지도가 정상적이라면 사용하기 쉬운 형태(2차원 배열)로 변환합니다.
* mlx 라이브러리를 이용해 그래픽을 그립니다.
- - -
</details>


<details>
    <summary>int	verify_map(char *path, t_map *map)</summary>
  
```c
typedef struct s_map
{
	int		row;
	int		col;
	int		empty_cnt;
	int		collectible_cnt;
	int		move_cnt;
	t_point	player;
	t_point	enemy;
	t_list	*exit;
	t_list	*collectible;
	t_list	*wall;
}t_map;

int	verify_map(char *path, t_map *map)
{
	int		fd;

	*map = (t_map){.collectible = 0, .exit = 0, .wall = 0};
	*map = (t_map){.move_cnt = 0, .collectible_cnt = 0};
	map->player = (t_point){.x = -1, .y = -1};
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nCannot open the file");
		return (1);
	}
	else if (read_map(fd, map))
	{
		printf("Error\nInvalid map file\n");
		ft_lstclear(&map->collectible, free);
		ft_lstclear(&map->exit, free);
		return (1);
	}
	close(fd);
	return (0);
}
```
* 이전에 만들었던 get_next_line을 활용하기 위해, fd를 열어주는 부분입니다.
* 그리고 map 구조체에 정보를 담기 위해 초기화합니다.
- - -
</details>

<details>
    <summary>static int	read_map(int fd, t_map *map)</summary>
  
```c
static int	read_map(int fd, t_map *map)
{
	char	*tmp;
	int		tmp_len;
	int		wall_cnt;

	tmp = get_next_line(fd);
	if (tmp == 0)
		return (1);
	map->col = ft_strlen(tmp);
	map->col -= (tmp[map->col - 1] == '\n');
	while (tmp)
	{
		wall_cnt = 0;
		tmp_len = ft_strlen(tmp);
		tmp_len -= (tmp[tmp_len - 1] == '\n');
		if (tmp_len != map->col || line_check(tmp, tmp_len, &wall_cnt, map))
			return (1);
		else if (!map->row && wall_cnt != map->col)
			return (1);
		map->row++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (wall_cnt != map->col || map->player.x == -1 \
	|| !map->collectible || !map->exit);
}
```
* 지도가 충족해야 할 조건을 확인합니다.
* 지도는 직사각형이여야 하므로 첫 번째 줄을 읽어와서, 그 줄의 길이를 저장해두고, 다른 줄을 받을 때 마다 첫 줄의 길이와 비교합니다.
* 지도는 벽에 둘러싸여야 하므로, 첫 번째 줄과, 마지막 줄은 벽의 갯수와 줄의 길이가 동일한지 확인하였습니다.
* 이 외의 다른 확인작업은 line_check() 함수에서 진행합니다.
- - -
</details>

<details>
    <summary>static int	line_check(char *line, int len, int *wall_cnt, t_map *map)</summary>
  
```c
static int	lst_point_append(int x, int y, t_list **lst)
{
	t_point	*new_point;
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (1);
	new->next = 0;
	new_point = (t_point *)malloc(sizeof(t_point));
	if (!new_point)
	{
		free(new);
		return (1);
	}
	new_point->x = x;
	new_point->y = y;
	new->content = new_point;
	ft_lstadd_front(lst, new);
	return (0);
}

static int	line_check(char *line, int len, int *wall_cnt, t_map *map)
{
	if (line[0] != '1' || line[len - 1] != '1')
		return (1);
	while (len--)
	{
		*wall_cnt += (line[len] == '1');
		if (line[len] == 'C')
		{
			lst_point_append(map->row, len, &map->collectible);
			map->collectible_cnt++;
		}
		else if (line[len] == 'E')
			lst_point_append(map->row, len, &map->exit);
		else if (line[len] == 'P' && map->player.x == -1)
			map->player = (t_point){.x = map->row, .y = len};
		else if (line[len] == '1')
			lst_point_append(map->row, len, &map->wall);
		else if (line[len] == '0')
			map->empty_cnt++;
		else
			return (1);
	}
	return (0);
}
```
* 저는 출구와, 수집품(collectible)은 여러개가 나올 수 있지만, 플레이어는 단 하나만 나와야 한다고 생각했습니다.
* 또한, 이 중 하나의 요소라도 존재하지 않는다면, 맵이 잘못된 것으로 판단하였습니다.
* 여러개가 나올 수 있는 요소는 연결 리스트를 이용했고, 플레이어는 좌표의 초깃값을 -1로 두어, 초깃값이 달라진 상태에서 한번 더 플레이어가 지도에 등장하면 오류로 처리했습니다.
* 또한 맵이 벽에 둘러싸여있어야 하므로 첫 번째 칸과, 마지막 칸이 벽인지도 확인해주었습니다.
- - -
</details>

<details>
    <summary>char	**make_table(t_map *map)</summary>
  
```c
char	**make_table(t_map *map)
{
	char	**table;
	int		i;

	table = (char **)malloc(sizeof(char **) * map->row);
	if (!table)
		return (0);
	i = map->row;
	while (i--)
	{
		table[i] = (char *)malloc(sizeof(char *) * map->col);
		if (!table[i])
		{
			while (i++ < map->row - 1)
				free(table[i]);
			free(table);
			return (0);
		}
		ft_memset(table[i], 0, map->col);
	}
	fill_table(table, map);
	make_enemy(table, map);
	return (table);
}
```
* 검증한 지도를 사용하기 편하게 할 수 있도록 2차원 배열을 할당하는 함수입니다.
- - -
</details>

<details>
    <summary>static void	fill_table(char **table, t_map *map)</summary>
  
```c
static void	fill_table(char **table, t_map *map)
{
	t_list	*tmp;

	tmp = map->collectible;
	while (tmp)
	{
		table[((t_point *)tmp->content)->x][((t_point *)tmp->content)->y] = 'C';
		tmp = tmp->next;
	}
	tmp = map->wall;
	while (tmp)
	{
		table[((t_point *)tmp->content)->x][((t_point *)tmp->content)->y] = 'W';
		tmp = tmp->next;
	}
	tmp = map->exit;
	while (tmp)
	{
		table[((t_point *)tmp->content)->x][((t_point *)tmp->content)->y] = 'Q';
		tmp = tmp->next;
	}
	table[map->player.x][map->player.y] = 'P';
}
```
* 할당한 2차원 배열에, 확인해뒀던 정보들을 모두 넣습니다.
- - -
</details>

<details>
    <summary>static void	make_enemy(char **table, t_map *map)</summary>
  
```c
size_t	__rand(void)
{
	static size_t	seed = 3847291;

	seed = seed * 1664525 + 1013904223;
	return (seed >> 16);
}

static void	make_enemy(char **table, t_map *map)
{
	t_point	tmp;

	if (map->empty_cnt < 10)
		return ;
	while (1)
	{
		tmp = (t_point){.x = __rand() % map->row, .y = __rand() % map->col};
		if (!table[tmp.x][tmp.y])
		{
			map->enemy = tmp;
			table[tmp.x][tmp.y] = 'E';
			return ;
		}
	}
}
```
* 지도에 존재하지 않는 적을 어디에, 어떻게 만들어야 할 까 고민을 꽤 오래 했는데, 완벽한 랜덤은 구현할 수 없더라도, 어느정도 임의의 결과를 만들기 위해 랜덤함수를 따로 만들어 사용했습니다.
* 시드값이 고정되어있고, 시드를 실행마다 임의의 값으로 바꿔줄 수는 없으므로, 항상 같은 결과가 나올 것입니다.
* 그러나 이 정도만 하더라도, 문제에서 요구하는 수준은 충분히 충족할 수 있다고 판단하였습니다.
* 랜덤함수를 이용해 임의의 좌표를 선택해서, 그 좌표에 적이 들어갈 수 있을 때 까지(빈 공간을 찾을 때 까지) 무한히 반복합니다.
* 너무 좁은 지도에서는 탈출이 불가능 할 지도 모른다는 생각에 빈 공간이 10개 이상일때만 적을 만들었습니다.
- - -
</details>

<details>
    <summary>t_assets	get_assets(t_vars *v)</summary>
  
```c
typedef struct s_assets
{
	void	*chest;
	void	*door;
	void	*ground;
	void	*player[2];
	void	*slime;
	void	*wall;
	void	*num[10];
	void	*sharp;
}t_assets;

t_assets	get_assets(t_vars *v)
{
	t_assets	r;
	int			t;

	r.chest = mlx_xpm_file_to_image(v->m, "./assets/chest.xpm", &t, &t);
	r.door = mlx_xpm_file_to_image(v->m, "./assets/door.xpm", &t, &t);
	r.ground = mlx_xpm_file_to_image(v->m, "./assets/ground.xpm", &t, &t);
	r.player[0] = mlx_xpm_file_to_image(v->m, "./assets/player1.xpm", &t, &t);
	r.player[1] = mlx_xpm_file_to_image(v->m, "./assets/player2.xpm", &t, &t);
	r.slime = mlx_xpm_file_to_image(v->m, "./assets/slime.xpm", &t, &t);
	r.wall = mlx_xpm_file_to_image(v->m, "./assets/wall.xpm", &t, &t);
	r.sharp = mlx_xpm_file_to_image(v->m, "./assets/num/#.xpm", &t, &t);
	r.num[0] = mlx_xpm_file_to_image(v->m, "./assets/num/0.xpm", &t, &t);
	r.num[1] = mlx_xpm_file_to_image(v->m, "./assets/num/1.xpm", &t, &t);
	r.num[2] = mlx_xpm_file_to_image(v->m, "./assets/num/2.xpm", &t, &t);
	r.num[3] = mlx_xpm_file_to_image(v->m, "./assets/num/3.xpm", &t, &t);
	r.num[4] = mlx_xpm_file_to_image(v->m, "./assets/num/4.xpm", &t, &t);
	r.num[5] = mlx_xpm_file_to_image(v->m, "./assets/num/5.xpm", &t, &t);
	r.num[6] = mlx_xpm_file_to_image(v->m, "./assets/num/6.xpm", &t, &t);
	r.num[7] = mlx_xpm_file_to_image(v->m, "./assets/num/7.xpm", &t, &t);
	r.num[8] = mlx_xpm_file_to_image(v->m, "./assets/num/8.xpm", &t, &t);
	r.num[9] = mlx_xpm_file_to_image(v->m, "./assets/num/9.xpm", &t, &t);
	return (r);
}
```
* 단순히 사용되는 이미지파일들을 불러오는 함수입니다.
- - -
</details>

<details>
    <summary>void	draw_image(t_vars *v, int moved)</summary>
  
```c
void	draw_image(t_vars *v, int moved)
{
	static int	p_state = 0;
	int			x;
	int			y;

	p_state++;
	if (p_state % 33 == 0)
	{
		move_enemy(v);
		moved = 2;
	}
	if (p_state % 50 == 0 && !moved)
		return ;
	x = v->map.row;
	while (x--)
	{
		y = v->map.col;
		while (y--)
			draw_area((t_point){x, y}, v, &v->assets, p_state);
	}
	if (p_state >= 100)
		p_state = 0;
	draw_count(v, &v->assets, moved);
}

```
* 이 함수가 호출되는 상황이 두 가지 있는데, 상황을 구분하기 위해 moved라는 인자를 이용합니다.
* 첫 번째는 플레이어가 움직이지 않은 경우입니다. 게임을 초기화하거나, 플레이어의 스프라이트를 바꾸기 위해, 또 적을 움직이기 위해 호출됩니다.
* 두 번째는 플레이어가 움직이는 경우입니다. 이동 횟수를 카운트해줘야 하기 때문에, 이런 방식으로 용도를 분리했습니다.
* 뒤에서 이 함수를 주기적으로 여러번 실행시켜주는 부분이 있는데, 이 점을 이용하여 특정 주기마다 플레이어의 스프라이트를 바꾸거나, 적을 움직이기 위해 p_state라는 값을 이용합니다.
* 이 외에는 단순히 2차원 배열에서 좌표 하나하나를 잡아, 그 자리에 이미지를 출력하도록 하는 함수입니다.
- - -
</details>

<details>
    <summary>static void	draw_area(t_point p, t_vars *v, t_assets *a, int p_state)</summary>
  
```c
static void	draw_area(t_point p, t_vars *v, t_assets *a, int p_state)
{
	if (v->table[p.x][p.y] == 'W')
		mlx_put_image_to_window(v->m, v->w, a->wall, p.y * 64, p.x * 64);
	else if (v->table[p.x][p.y] != 'W')
	{
		mlx_put_image_to_window(v->m, v->w, a->ground, p.y * 64, p.x * 64);
		if (v->table[p.x][p.y] == 'C')
			mlx_put_image_to_window(v->m, v->w, a->chest, p.y * 64, p.x * 64);
		else if (v->table[p.x][p.y] == 'P')
			mlx_put_image_to_window(v->m, v->w, \
				a->player[p_state / 50 & 1], p.y * 64, p.x * 64);
		else if (v->table[p.x][p.y] == 'Q')
			mlx_put_image_to_window(v->m, v->w, a->door, p.y * 64, p.x * 64);
		else if (v->table[p.x][p.y] == 'E')
			mlx_put_image_to_window(v->m, v->w, a->slime, p.y * 64, p.x * 64);
	}
}
```
* 인자로 받은 좌표에, 64*64 픽셀의 미리 불러왔던 이미지를 출력합니다.
- - -
</details>

<details>
    <summary>static void	draw_count(t_vars *v, t_assets *a, int moved)</summary>
  
```c
static void	draw_count(t_vars *v, t_assets *a, int moved)
{
	int	cnt;
	int	digits;
	int	offset;

	if (moved == 1)
		printf("move count: #%d\n", v->map.move_cnt);
	cnt = v->map.move_cnt;
	digits = 0;
	offset = v->map.col * 64 - 64;
	while (cnt)
	{
		mlx_put_image_to_window(v->m, v->w, \
			a->num[cnt % 10], offset - digits * 18, 16);
		digits++;
		cnt /= 10;
	}
	if (digits)
		mlx_put_image_to_window(v->m, v->w, \
			a->sharp, offset - digits * 18 - 16, 16);
}
```
* 게임 화면 위에 이동 횟수를 적기 위해 지도가 다 그려진 후 호출됩니다.
* 지도가 다시 그려질때마다, 이동 횟수 위에 덮어씌워지기 때문에 이동 횟수도 다시 그려줘야 합니다.
* 단순히 이동 횟수를 한 글자씩 떼어와서, 한 칸씩 옆으로 옮기며 그립니다.
* moved가 1일때는 플레이어가 움직였다는 것이기에 그 때만 shell에 이동 횟수를 출력합니다.
- - -
</details>

<details>
    <summary>static int	key_hook(int keycode, t_vars *vars)</summary>
  
```c
static int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		close_game(vars);
	if (vars->map.player.x == -1)
		return (0);
	if (keycode == KEY_W || keycode == KEY_A \
		|| keycode == KEY_S || keycode == KEY_D)
		move_player(keycode, vars);
	return (0);
}
```
* mlx_hook 을 이용해 호출되는 함수입니다.
* 키보드 입력이 있다면, 입력받은 키가 무엇인지 확인한 후, 상황에 따른 동작을 하는 함수를 호출합니다.
* 추후 나오겠지만, 플레이어의 x좌표가 -1이라면, 플레이어가 죽은 상태이므로 플레이어를 더 이상 움직이지 않습니다.
- - -
</details>

<details>
    <summary>void	move_player(int c, t_vars *v)</summary>
  
```c
void	move_player(int c, t_vars *v)
{
	static int	way[14][2] = {[KEY_W] = {-1, 0}, \
		[KEY_A] = {0, -1}, [KEY_S] = {1, 0}, [KEY_D] = {0, 1}};
	t_point		next;

	next = (t_point){v->map.player.x + way[c][0], v->map.player.y + way[c][1]};
	if (v->table[next.x][next.y] == 'W')
		return ;
	else if (v->table[next.x][next.y] == 'Q' && v->map.collectible_cnt)
		return ;
	else if (v->table[next.x][next.y] == 'C')
		v->map.collectible_cnt--;
	else if (v->table[next.x][next.y] == 'E')
	{
		v->table[v->map.player.x][v->map.player.y] = '\0';
		v->map.player.x = -1;
		draw_image(v, 0);
		return ;
	}
	else if (v->table[next.x][next.y] == 'Q')
		close_game(v);
	v->table[v->map.player.x][v->map.player.y] = 0;
	v->map.player = next;
	v->table[v->map.player.x][v->map.player.y] = 'P';
	v->map.move_cnt++;
	draw_image(v, 1);
}
```
* 플레이어가 이동하려고 하는 방향으로 다음 좌표를 구해서, 그 좌표로 이동할 수 있는지 확인합니다.
* 이동하려는 곳이 출구인데, 수집품을 다 못 모았다면 그쪽으로는 이동할 수 없고, 벽이여도 마찬가지입니다.
* 적을 만난다면 플레이어를 죽은 것으로 처리하고(x좌표를 -1로 만든다) 맵에서 플레이어를 지웁니다.
* 이동했다면 플레이어의 좌표를 바꿔주고, 지도 전체를 다시 그립니다.
- - -
</details>

<details>
    <summary>void	move_enemy(t_vars *v)</summary>
  
```c
void	move_enemy(t_vars *v)
{
	static int	way[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	t_point		next;
	int			r;

	while (1)
	{
		r = __rand() % 4;
		next = (t_point){v->map.enemy.x + way[r][0], \
			v->map.enemy.y + way[r][1]};
		if (v->table[next.x][next.y] == 'W' || v->table[next.x][next.y] == 'Q' \
			|| v->table[next.x][next.y] == 'C')
			continue ;
		if (v->table[next.x][next.y] == 'P')
		{
			v->table[v->map.player.x][v->map.player.y] = '\0';
			v->map.player.x = -1;
		}
		v->table[v->map.enemy.x][v->map.enemy.y] = 0;
		v->map.enemy = next;
		v->table[v->map.enemy.x][v->map.enemy.y] = 'E';
		break ;
	}
}
```
* 위에서 설명한 플레이어 이동함수와 거의 동일합니다.
* 다른 점은 다음에 이동할 방향을 랜덤으로 결정하는 것 뿐입니다.
* 이동할 수 있는 방향이 나올때까지 무한히 반복합니다.
- - -
</details>

<details>
    <summary>int	close_game(t_vars *vars)</summary>
  
```c
int	close_game(t_vars *vars)
{
	mlx_destroy_window(vars->m, vars->w);
	free_elements(vars);
	exit(0);
}
```
* 게임을 종료하는 상황(X를 눌렀거나, ESC를 눌렀거나, 출구로 탈출한 경우)에서 할당했던 모든 메모리를 free하기 위해 호출됩니다.
- - -
</details>

<details>
    <summary>static void	free_elements(t_vars *vars)</summary>
  
```c
static void	free_elements(t_vars *vars)
{
	int	n;

	ft_lstclear(&vars->map.collectible, free);
	ft_lstclear(&vars->map.exit, free);
	n = vars->map.row;
	while (n--)
		free(vars->table[n]);
	free(vars->table);
}
```
* 만들었던 연결 리스트의 노드를 모두 삭제하고, 2차원 배열 또한 삭제합니다.
* mlx를 위해 할당한 포인터들은 free시 오류가 나거나, 누수가 발생하므로 따로 작업을 해주지는 않았습니다.
- - -
</details>

- - -

mlx 라이브러리 사용법은 다음 링크를 참고했습니다.

https://harm-smits.github.io/42docs/libs/minilibx.html
	
<img width="944" alt="image" src="https://user-images.githubusercontent.com/67845112/194150962-79b5bb79-951b-47ad-8f22-745612610386.png">

<img width="407" alt="image" src="https://user-images.githubusercontent.com/67845112/188685202-dfadc8f8-94ea-4afa-8c24-41e44a3d4a50.png">

[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fr4pidstart%2Fft_so_long%2F&count_bg=%23000000&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=hits&edge_flat=false)](https://hits.seeyoufarm.com)
