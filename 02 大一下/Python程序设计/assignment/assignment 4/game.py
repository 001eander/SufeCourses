from dataclasses import dataclass


@dataclass
class Payoff:
    """
    给定如下结构的收益矩阵

        payoff_matrix = {
            ('C', 'C'): (R, R),
            ('C', 'D'): (S, T),
            ('D', 'C'): (T, S),
            ('D', 'D'): (P, P),
        }
    其中，
    R为 player 1 在payoff_matrix中('C', 'C')格子的得分，
      该字母是Reward（奖励）的简称，表示双方都选择合作时的收益；
    P为 player 1 在payoff_matrix中('D', 'D')格子的得分，
      该字母是Punishment（惩罚）的简称，表示双方都选择背叛时的收益；
    S为 player 1 在payoff_matrix中('C', 'D')格子的得分，
      该字母是Sucker's payoff（傻瓜的收益）的简称，表示一方选择合作而另一方选择背叛时，合作方的收益；
    T为 player 1 在payoff_matrix中('D', 'C')格子的得分，是Temptation的简称，
      该字母是Temptation（诱惑）的简称，表示一方选择背叛而另一方选择合作时，背叛方的收益。

    上述记号方式的来源可参考[1]和[2]

    注意到囚徒困境的核心设定可以一般性地描述为 T > R > P > S

    参考：
    [1] https://en.wikipedia.org/wiki/Prisoner's_dilemma
    [2] Press, W. H., & Dyson, F. J. (2012). Iterated Prisoner’s Dilemma contains strategies that dominate any evolutionary opponent.
        Proceedings of the National Academy of Sciences, 109(26), 10409–10413. https://doi.org/10.1073/pnas.1206569109
    """

    R: int = 3
    P: int = 1
    S: int = 0
    T: int = 5

    def __post_init__(self):
        assert self.T > self.R > self.P > self.S
        self.matrix = {
            ("C", "C"): (self.R, self.R),
            ("C", "D"): (self.S, self.T),
            ("D", "C"): (self.T, self.S),
            ("D", "D"): (self.P, self.P),
        }

    def __repr__(self):
        matrix_str = (
            f"Payoff Matrix:\n"
            f"                   player 2 \n"
            f"                   C       D\n"
            f"player 1  C     ({self.R}, {self.R})  ({self.S}, {self.T})\n"
            f"          D     ({self.T}, {self.S})  ({self.P}, {self.P})"
        )
        return matrix_str


# 玩家基类
class Player:
    def __init__(self, name: str):
        self.name: str = name
        self.history: list[str] = []
        self.cooperations: int = 0
        self.defections: int = 0

    def move(self, opponent) -> str:
        """返回 'C'（合作）或 'D'（背叛）"""
        raise NotImplementedError("子类必须实现 move 方法")

    def record_moves(self, action: str) -> None:
        self.history.append(action)
        if action == "C":
            self.cooperations += 1
        elif action == "D":
            self.defections += 1
        else:
            raise ValueError(f"Invalid action: {action}")

    def reset(self) -> None:
        self.history.clear()
        self.cooperations = 0
        self.defections = 0

    def __repr__(self) -> str:
        return f"{self.__class__.__name__}('{self.name}')"
