################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/backend/utils/adt/acl.c \
../src/backend/utils/adt/array_userfuncs.c \
../src/backend/utils/adt/arrayfuncs.c \
../src/backend/utils/adt/arrayutils.c \
../src/backend/utils/adt/ascii.c \
../src/backend/utils/adt/bool.c \
../src/backend/utils/adt/cash.c \
../src/backend/utils/adt/char.c \
../src/backend/utils/adt/date.c \
../src/backend/utils/adt/datetime.c \
../src/backend/utils/adt/datum.c \
../src/backend/utils/adt/dbsize.c \
../src/backend/utils/adt/domains.c \
../src/backend/utils/adt/encode.c \
../src/backend/utils/adt/enum.c \
../src/backend/utils/adt/float.c \
../src/backend/utils/adt/format_type.c \
../src/backend/utils/adt/formatting.c \
../src/backend/utils/adt/genfile.c \
../src/backend/utils/adt/geo_ops.c \
../src/backend/utils/adt/geo_selfuncs.c \
../src/backend/utils/adt/inet_net_ntop.c \
../src/backend/utils/adt/inet_net_pton.c \
../src/backend/utils/adt/int.c \
../src/backend/utils/adt/int8.c \
../src/backend/utils/adt/like.c \
../src/backend/utils/adt/like_match.c \
../src/backend/utils/adt/lockfuncs.c \
../src/backend/utils/adt/mac.c \
../src/backend/utils/adt/misc.c \
../src/backend/utils/adt/nabstime.c \
../src/backend/utils/adt/name.c \
../src/backend/utils/adt/network.c \
../src/backend/utils/adt/numeric.c \
../src/backend/utils/adt/numutils.c \
../src/backend/utils/adt/oid.c \
../src/backend/utils/adt/oracle_compat.c \
../src/backend/utils/adt/pg_locale.c \
../src/backend/utils/adt/pg_lzcompress.c \
../src/backend/utils/adt/pgstatfuncs.c \
../src/backend/utils/adt/pseudotypes.c \
../src/backend/utils/adt/quote.c \
../src/backend/utils/adt/regexp.c \
../src/backend/utils/adt/regproc.c \
../src/backend/utils/adt/ri_triggers.c \
../src/backend/utils/adt/rowtypes.c \
../src/backend/utils/adt/ruleutils.c \
../src/backend/utils/adt/selfuncs.c \
../src/backend/utils/adt/tid.c \
../src/backend/utils/adt/timestamp.c \
../src/backend/utils/adt/trigfuncs.c \
../src/backend/utils/adt/tsginidx.c \
../src/backend/utils/adt/tsgistidx.c \
../src/backend/utils/adt/tsquery.c \
../src/backend/utils/adt/tsquery_cleanup.c \
../src/backend/utils/adt/tsquery_gist.c \
../src/backend/utils/adt/tsquery_op.c \
../src/backend/utils/adt/tsquery_rewrite.c \
../src/backend/utils/adt/tsquery_util.c \
../src/backend/utils/adt/tsrank.c \
../src/backend/utils/adt/tsvector.c \
../src/backend/utils/adt/tsvector_op.c \
../src/backend/utils/adt/tsvector_parser.c \
../src/backend/utils/adt/txid.c \
../src/backend/utils/adt/uuid.c \
../src/backend/utils/adt/varbit.c \
../src/backend/utils/adt/varchar.c \
../src/backend/utils/adt/varlena.c \
../src/backend/utils/adt/version.c \
../src/backend/utils/adt/windowfuncs.c \
../src/backend/utils/adt/xid.c \
../src/backend/utils/adt/xml.c 

OBJS += \
./src/backend/utils/adt/acl.o \
./src/backend/utils/adt/array_userfuncs.o \
./src/backend/utils/adt/arrayfuncs.o \
./src/backend/utils/adt/arrayutils.o \
./src/backend/utils/adt/ascii.o \
./src/backend/utils/adt/bool.o \
./src/backend/utils/adt/cash.o \
./src/backend/utils/adt/char.o \
./src/backend/utils/adt/date.o \
./src/backend/utils/adt/datetime.o \
./src/backend/utils/adt/datum.o \
./src/backend/utils/adt/dbsize.o \
./src/backend/utils/adt/domains.o \
./src/backend/utils/adt/encode.o \
./src/backend/utils/adt/enum.o \
./src/backend/utils/adt/float.o \
./src/backend/utils/adt/format_type.o \
./src/backend/utils/adt/formatting.o \
./src/backend/utils/adt/genfile.o \
./src/backend/utils/adt/geo_ops.o \
./src/backend/utils/adt/geo_selfuncs.o \
./src/backend/utils/adt/inet_net_ntop.o \
./src/backend/utils/adt/inet_net_pton.o \
./src/backend/utils/adt/int.o \
./src/backend/utils/adt/int8.o \
./src/backend/utils/adt/like.o \
./src/backend/utils/adt/like_match.o \
./src/backend/utils/adt/lockfuncs.o \
./src/backend/utils/adt/mac.o \
./src/backend/utils/adt/misc.o \
./src/backend/utils/adt/nabstime.o \
./src/backend/utils/adt/name.o \
./src/backend/utils/adt/network.o \
./src/backend/utils/adt/numeric.o \
./src/backend/utils/adt/numutils.o \
./src/backend/utils/adt/oid.o \
./src/backend/utils/adt/oracle_compat.o \
./src/backend/utils/adt/pg_locale.o \
./src/backend/utils/adt/pg_lzcompress.o \
./src/backend/utils/adt/pgstatfuncs.o \
./src/backend/utils/adt/pseudotypes.o \
./src/backend/utils/adt/quote.o \
./src/backend/utils/adt/regexp.o \
./src/backend/utils/adt/regproc.o \
./src/backend/utils/adt/ri_triggers.o \
./src/backend/utils/adt/rowtypes.o \
./src/backend/utils/adt/ruleutils.o \
./src/backend/utils/adt/selfuncs.o \
./src/backend/utils/adt/tid.o \
./src/backend/utils/adt/timestamp.o \
./src/backend/utils/adt/trigfuncs.o \
./src/backend/utils/adt/tsginidx.o \
./src/backend/utils/adt/tsgistidx.o \
./src/backend/utils/adt/tsquery.o \
./src/backend/utils/adt/tsquery_cleanup.o \
./src/backend/utils/adt/tsquery_gist.o \
./src/backend/utils/adt/tsquery_op.o \
./src/backend/utils/adt/tsquery_rewrite.o \
./src/backend/utils/adt/tsquery_util.o \
./src/backend/utils/adt/tsrank.o \
./src/backend/utils/adt/tsvector.o \
./src/backend/utils/adt/tsvector_op.o \
./src/backend/utils/adt/tsvector_parser.o \
./src/backend/utils/adt/txid.o \
./src/backend/utils/adt/uuid.o \
./src/backend/utils/adt/varbit.o \
./src/backend/utils/adt/varchar.o \
./src/backend/utils/adt/varlena.o \
./src/backend/utils/adt/version.o \
./src/backend/utils/adt/windowfuncs.o \
./src/backend/utils/adt/xid.o \
./src/backend/utils/adt/xml.o 

C_DEPS += \
./src/backend/utils/adt/acl.d \
./src/backend/utils/adt/array_userfuncs.d \
./src/backend/utils/adt/arrayfuncs.d \
./src/backend/utils/adt/arrayutils.d \
./src/backend/utils/adt/ascii.d \
./src/backend/utils/adt/bool.d \
./src/backend/utils/adt/cash.d \
./src/backend/utils/adt/char.d \
./src/backend/utils/adt/date.d \
./src/backend/utils/adt/datetime.d \
./src/backend/utils/adt/datum.d \
./src/backend/utils/adt/dbsize.d \
./src/backend/utils/adt/domains.d \
./src/backend/utils/adt/encode.d \
./src/backend/utils/adt/enum.d \
./src/backend/utils/adt/float.d \
./src/backend/utils/adt/format_type.d \
./src/backend/utils/adt/formatting.d \
./src/backend/utils/adt/genfile.d \
./src/backend/utils/adt/geo_ops.d \
./src/backend/utils/adt/geo_selfuncs.d \
./src/backend/utils/adt/inet_net_ntop.d \
./src/backend/utils/adt/inet_net_pton.d \
./src/backend/utils/adt/int.d \
./src/backend/utils/adt/int8.d \
./src/backend/utils/adt/like.d \
./src/backend/utils/adt/like_match.d \
./src/backend/utils/adt/lockfuncs.d \
./src/backend/utils/adt/mac.d \
./src/backend/utils/adt/misc.d \
./src/backend/utils/adt/nabstime.d \
./src/backend/utils/adt/name.d \
./src/backend/utils/adt/network.d \
./src/backend/utils/adt/numeric.d \
./src/backend/utils/adt/numutils.d \
./src/backend/utils/adt/oid.d \
./src/backend/utils/adt/oracle_compat.d \
./src/backend/utils/adt/pg_locale.d \
./src/backend/utils/adt/pg_lzcompress.d \
./src/backend/utils/adt/pgstatfuncs.d \
./src/backend/utils/adt/pseudotypes.d \
./src/backend/utils/adt/quote.d \
./src/backend/utils/adt/regexp.d \
./src/backend/utils/adt/regproc.d \
./src/backend/utils/adt/ri_triggers.d \
./src/backend/utils/adt/rowtypes.d \
./src/backend/utils/adt/ruleutils.d \
./src/backend/utils/adt/selfuncs.d \
./src/backend/utils/adt/tid.d \
./src/backend/utils/adt/timestamp.d \
./src/backend/utils/adt/trigfuncs.d \
./src/backend/utils/adt/tsginidx.d \
./src/backend/utils/adt/tsgistidx.d \
./src/backend/utils/adt/tsquery.d \
./src/backend/utils/adt/tsquery_cleanup.d \
./src/backend/utils/adt/tsquery_gist.d \
./src/backend/utils/adt/tsquery_op.d \
./src/backend/utils/adt/tsquery_rewrite.d \
./src/backend/utils/adt/tsquery_util.d \
./src/backend/utils/adt/tsrank.d \
./src/backend/utils/adt/tsvector.d \
./src/backend/utils/adt/tsvector_op.d \
./src/backend/utils/adt/tsvector_parser.d \
./src/backend/utils/adt/txid.d \
./src/backend/utils/adt/uuid.d \
./src/backend/utils/adt/varbit.d \
./src/backend/utils/adt/varchar.d \
./src/backend/utils/adt/varlena.d \
./src/backend/utils/adt/version.d \
./src/backend/utils/adt/windowfuncs.d \
./src/backend/utils/adt/xid.d \
./src/backend/utils/adt/xml.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/utils/adt/%.o: ../src/backend/utils/adt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


