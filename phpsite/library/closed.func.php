<?php

/*
 * ע�⣬�����õ���EncryptedPhoneNumber, UserEntry, UpdateRequest, UpdatePackage
 * ȫ������C���Զ����struct�������data.h��
 * 
 * ��֪�������php��Ҳ���Դ������ִ�2�������ݣ�
 */

/**
 * �û�ע��
 * @param $encryptedPhoneNumber ����PADDING���÷�������Կ�����ܺ�õ���EncryptedPhoneNumber
 * @param $userEntry �÷�������Կ�����ܺ�õ���UserEntry
 * @return ���ע���Unix timestamp��0��ʾʧ��
 */
function register($encryptedPhoneNumber, $userEntry){
	//TODO
}

/**
 * �û������Լ�����Ϣ
 * @param $encryptedPhoneNumber ����PADDING���÷�������Կ�����ܺ�õ���EncryptedPhoneNumber
 * @param $userEntry ���÷�������Կ�����ܣ������û��Լ���˽Կ���ܺ�õ���UserEntry
 * @return ���ע���Unix timestamp��0��ʾʧ��
 */
function update($encryptedPhoneNumber, $userEntry){
	//TODO
}

/**
 * �û���ȡ�Լ���ϵ�˵�������Ϣ
 * @param $encryptedPhoneNumber ����PADDING���÷�������Կ�����ܺ�õ���EncryptedPhoneNumber
 * @param $updateRequest ��ͨ��UpdateRequest�����а�������Ҫ�����Щ��ϵ�˵�������Ϣ
 * @return ��õ�UpdatePackage�������˸��¹�����ϵ����Ϣ���Ѿ�����ʱ����������
 */
function getUpdatePackage($encryptedPhoneNumber, $updateRequest){
	//TODO
}

?>
