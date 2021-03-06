#include <jni.h>
#include <string>

#include <cstring>
#include <cstdlib>
#include <cassert>
#include <stdexcept>

#include "../../../../../Fir1.h"

extern "C" {

jlong
Java_uk_me_berndporr_firj_Fir1_getInstance(JNIEnv *env,
                                           jclass,
                                           jdoubleArray coeffArray) {

    double *coeffValues = env->GetDoubleArrayElements(coeffArray, 0);
    unsigned nTaps = (unsigned) env->GetArrayLength(coeffArray);

    Fir1 *fir = new Fir1(coeffValues, nTaps);

    env->ReleaseDoubleArrayElements(coeffArray, coeffValues, 0);

    return (jlong) fir;
}


jlong
Java_uk_me_berndporr_firj_Fir1_getInstanceLMS(JNIEnv *env,
                                              jclass,
                                              jint nTaps) {

    Fir1 *fir = new Fir1((unsigned)nTaps);
    return (jlong) fir;
}


jint Java_uk_me_berndporr_firj_Fir1_getTaps(JNIEnv *,
                                            jclass,
                                            jlong instance) {
    Fir1 *fir = (Fir1 *) instance;
    if (fir == NULL) return 0;
    return (jint)(fir->getTaps());
}


jdouble
Java_uk_me_berndporr_firj_Fir1_filter(JNIEnv *,
                                      jclass,
                                      jlong instance,
                                      jdouble value) {
    Fir1 *fir = (Fir1 *) instance;
    if (fir == NULL) return 0;
    return fir->filter(value);
}


void
Java_uk_me_berndporr_firj_Fir1_lmsUpdate(JNIEnv *,
                                         jclass,
                                         jlong instance,
                                         jdouble error) {
    Fir1 *fir = (Fir1 *) instance;
    return fir->lms_update(error);
}


void
Java_uk_me_berndporr_firj_Fir1_setLearningRate(JNIEnv *,
                                               jclass,
                                               jlong instance,
                                               jdouble mu) {
    Fir1 *fir = (Fir1 *) instance;
    return fir->setLearningRate(mu);
}


jdouble
Java_uk_me_berndporr_firj_Fir1_getTapInputPower(JNIEnv *,
                                                jclass,
                                                jlong instance) {
    Fir1 *fir = (Fir1 *) instance;
    return fir->getTapInputPower();
}


void Java_uk_me_berndporr_firj_Fir1_releaseInstance(JNIEnv *,
                                                    jclass,
                                                    jlong instance) {
    Fir1 *fir = (Fir1 *) instance;
    if (fir == NULL) return;
    delete fir;
}


}