import random

from game import Player, Payoff


# 策略类：总是合作
class AlwaysCooperatePlayer(Player):
    def move(self, opponent: Player) -> str:
        return "C"


# 策略类：总是背叛
class AlwaysDefectPlayer(Player):
    def move(self, opponent: Player) -> str:
        return "D"


# 策略类：随机
class RandomPlayer(Player):
    def move(self, opponent: Player) -> str:
        return random.choice(["C", "D"])


# 策略类：唐宁策略
class DowningPlayer(Player):
    def __init__(self, name: str, payoff: Payoff):
        super().__init__(name)
        self.payoff = payoff
        self.number_opponent_cooperations_in_response_to_C = 0
        self.number_opponent_cooperations_in_response_to_D = 0

    def move(self, opponent: Player) -> str:
        """唐宁策略（Downing Strategy）是一种基于贝叶斯估计 + 最优响应的囚徒困境博弈策略，由 凯文·唐宁（Kevin Downing）提出。

        核心思路：

        记“C_s”代表事件“上一轮自己选择合作”，“D_s”代表事件“上一轮自己选择背叛”，

        “C_o”代表事件“这一轮对手选择合作”，“D_o”代表事件“这一轮对手选择背叛”。

        另记：
        + alpha = P(C_o | C_s) 表示在自己上一轮选择合作的情况下，对手这一轮选择合作的概率，
        + beta =  P(C_o | D_s) 表示在自己上一轮选择背叛的情况下，对手这一轮选择合作的概率。

        则有
        + 1-alpha = P(D_o | C_s) 表示在自己上一轮选择合作的情况下，对手这一轮选择背叛的概率，
        + 1-beta = P(D_o | D_s)  表示在自己上一轮选择背叛的情况下，对手这一轮选择背叛的概率。

        根据收益矩阵中：R表示双方都选择合作时的收益；P表示双方都选择背叛时的收益；
        S表示一方选择合作而另一方选择背叛时，合作方的收益；T表示一方选择背叛而另一方选择合作时，背叛方的收益。
        则不难有如下推论：
        + 长期来看，如果自己一直选择合作，平均每轮的期望收益为 E_C = alpha * R + (1 - alpha) * S
        + 长期来看，如果自己一直选择背叛，平均每轮的期望收益为 E_D = beta  * T + (1 - beta) *  P

        在第N轮，玩家根据历史观测到的信息，得到alpha和beta的最新估计值，并执行如下策略：
        + 若 E_C > E_D，则选择合作；
        + 若 E_C < E_D，则选择背叛；
        + 若 E_C = E_D，则选择跟上一轮自身策略相反的策略。

        注意到，根据囚徒困境的核心设定 T > R > P > S，
        如果在第1轮定义 alpha = beta = 0.5，则有 E_C = (R+S)/2 < (T+P)/2 = E_D，因此第1轮一定选择背叛。

        进一步，如果在第1轮对方选择合作，则约定将beta更新为 beta = 1，而alpha保持估计值0.5不变。
        此时有 E_C = (R+S)/2 < T = E_D，因此第2轮一定还选择背叛。
        反之，则更新beta的估计值为 beta = 0，此时有 E_C = (R+S)/2 且 E_D = P，需要进一步判断。

        不同于前面的简单策略，在唐宁策略中，下一步行动，需要通过条件概率估计对手的合作倾向（alpha，beta），再基于收益矩阵计算长期期望得分，做出理性决策。

        因此需要添加两个属性，来记录对手对于己方行动的回应，并在比赛过程中（move方法）进行更新，在比赛结束后进行重置（重载reset方法）。
        """

        round_number = len(self.history) + 1

        if round_number == 1:
            return "D"

        if round_number == 2:
            if opponent.history[-1] == "C":
                self.number_opponent_cooperations_in_response_to_C += 1
            return "D"

        if self.history[-2] == "C" and opponent.history[-1] == "C":
            self.number_opponent_cooperations_in_response_to_C += 1
        if self.history[-2] == "D" and opponent.history[-1] == "C":
            self.number_opponent_cooperations_in_response_to_D += 1

        # Adding 1 to cooperations for assumption that first opponent move
        # being a response to a cooperation.
        alpha = self.number_opponent_cooperations_in_response_to_C / (
            self.cooperations + 1
        )
        # Adding 2 to defections on the assumption that the first two
        # moves are defections, which may not be true in a noisy match
        beta = self.number_opponent_cooperations_in_response_to_D / max(
            self.defections, 2
        )

        E_C = alpha * self.payoff.R + (1 - alpha) * self.payoff.S
        E_D = beta * self.payoff.T + (1 - beta) * self.payoff.P

        if E_C > E_D:
            return "C"
        elif E_C < E_D:
            return "D"
        else:
            return "D" if self.history[-1] == "C" else "C"

    def reset(self) -> None:
        super().reset()
        self.number_opponent_cooperations_in_response_to_C = 0
        self.number_opponent_cooperations_in_response_to_D = 0
