//
// Created by robso on 5/16/2017.
//

#ifndef TRABALHO2_SHOOTER_H
#define TRABALHO2_SHOOTER_H

/* Esta classe provê a representação de um atirador, que provê
 * a habilidade de atirar e perceber o resultado dos tiros para quem a herda.
 */
class Shooter {
public:
    virtual void hit_target() = 0;
    virtual bool has_shot() = 0;
};

#endif //TRABALHO2_SHOOTER_H
