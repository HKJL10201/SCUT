import random

def poker_game():
    """
    :rtype: List[List[str]]
    """

    # 红桃, 黑桃, 梅花, 方块
    suit = ['H', 'S', 'C', 'D']
    nums = [str(i) for i in range(1, 11)] + ['J', 'Q', 'K']

    #print(nums)

    # 请使用推导式生成所有的扑克牌，形如[H1, H2, ..., HK, S1, S2, ..., DK]
    all_cards =[]
    for s in suit:
        for n in nums:
            all_cards+=[s+n]

    # 加入大小王
    all_cards += ['RJ', "BJ"]

    # 洗牌
    random.shuffle(all_cards)

    #print(all_cards)

    # 请自行设计发牌规则，为3个玩家发牌。
    # 最终结果保存在results中，其中每个list保存一个玩家的扑克牌
    results = [[] for _ in range(3)]

    # 发牌代码写在下方
    for i in range(0,54):
        results[i%3].append(all_cards[i])

    return results

poker=poker_game()
print(poker)