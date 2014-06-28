/* 
 * File:   UniformSetting.h
 * Author: chris
 *
 * Created on June 1, 2014, 8:17 PM
 */

#ifndef GLUNIFORMSETTING_H
#define	GLUNIFORMSETTING_H

#include "../REND/UniformSetting.h"
#include "../ERR/ERR.h"

namespace GL {

    template <int N, typename T, char S>
    class UniformSetting : public REND::UniformSetting {
    public:

        UniformSetting(const REND::Uniform& uniform, bool allocate)
        : REND::UniformSetting(uniform)
        , m_data(0)
        , m_allocate(allocate) {
            if (allocate) {
                int quantity = 0;
                if (S == 'M')
                    quantity = N * N;
                else
                    quantity = N;
                m_data = new T[quantity];
            }
        }

        virtual ~UniformSetting() {
            if (m_allocate && m_data)
                delete [] m_data;

        }

        virtual void set() const {
            THROWS("NOT IMPLEMENTED");
        }

        virtual void set(const void* data) const {
            THROWS("NOT IMPLEMENTED");
        }

        virtual void* getRawData() {
            return m_data;
        }

        T* getData() {
            return m_data;
        }

        void setData(T* data) {
            m_data = data;
        }
    private:
        T* m_data;
        bool m_allocate;
    };

}
#endif	/* GLUNIFORMSETTING_H */

