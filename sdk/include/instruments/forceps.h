#ifndef INSTRUMENTS_FORCEPS_H
#define INSTRUMENTS_FORCEPS_H

#include <vector>
#include <cstdint>
#include <memory>

#include "abstract_instrument.h"

class Forceps : public AbstractInstrument
{
public:
    explicit Forceps(const char* serial_port_name);
    ~Forceps() override;

    /**
     * @brief Initializes the instrument.
     * 
     * This function initializes the instrument, ensuring it is ready for use.
     * 
     * @return true if initialization is successful, false otherwise.
     */
    bool initialize() override;

    /**
     * @brief Uninitializes the instrument.
     * 
     * This function performs the de-initialization of the instrument, including the destruction
     * of associated resources. After calling this function, the instrument should not be used.
     * 
     * @return true if uninitialization is successful, false otherwise.
     */
    bool uninitialize() override;

    /**
     * @brief Controls the motion of the instrument.
     *
     * This function controls the motion of the instrument.
     * It adjusts the velocity of each DOF according to the provided vector.
     * Each time the function is called, the control lasts for 50 ms.
     * If the function is called again within 50 ms, the new control command will be executed.
     *
     * @param velocities A vector containing the motion speeds for each DOF.
     */
    void control(const std::vector<int16_t> &velocities) override;

private:
    const std::unique_ptr<class ForcepsImpl> impl_;
};

#endif // INSTRUMENTS_FORCEPS_H
